#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    std::cout << "drivers :" << std::endl;
//    qDebug() << QSqlDatabase::drivers();

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();

    maindb = instance.get_db();


    update_tables();

    ui->fromDateEdit->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month() , 1));
    ui->toDateEdit->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month() , QDate::currentDate().daysInMonth()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlDatabase MainWindow::getdb(){
    return maindb;
}


void MainWindow::on_camionsButton_clicked()
{
    DisplayCamions* camDisp = new DisplayCamions(this);
    qDebug() << "clicked on Camions";
    camDisp->exec();
}

void MainWindow::on_chauffeursButton_clicked()
{
    DisplayChauffeurs* chauffDisp = new DisplayChauffeurs(this);
    qDebug() << "clicked on Chauffeurs";
    chauffDisp->exec();
    update_tables();
}

void MainWindow::on_tourneesButton_clicked()
{
    DisplayTournee* dispTour = new DisplayTournee(this);
    qDebug() << "clicked on Tournées";
    dispTour->exec();
    update_tables();
}

void MainWindow::on_clientsButton_clicked()
{
    DisplayClient* dispC = new DisplayClient(this);
    dispC->exec();
}



void MainWindow::create_tables(){
    QSqlQuery query = QSqlQuery(maindb);

    if(!query.exec("CREATE TABLE IF NOT EXISTS Chauffeurs (id INTEGER PRIMARY KEY, nom TEXT, prenom TEXT)")) {
         QMessageBox::critical(this, "Erreur SQL creating Chauffeur", query.lastError().text());
    }

    if(!query.exec("CREATE TABLE IF NOT EXISTS Tournees (nom TEXT PRIMARY KEY, client TEXT, prix FLOAT, chauffeur_nom TEXT, chauffeur_prenom TEXT, camion TEXT)")) {
         QMessageBox::critical(this, "Erreur SQL creating Tournee", query.lastError().text());
    }

    if(!query.exec("CREATE TABLE IF NOT EXISTS Clients (name TEXT PRIMARY KEY, city TEXT)")){
        QMessageBox::critical(this, "Erreur SQL creating client", query.lastError().text());
    }
}


void MainWindow::yellow_weekends(QDate& from_date){
    QLocale locale = QLocale(QLocale::French, QLocale::France);

    QDate buffer = from_date;
    QFont font;
    font.setCapitalization(QFont::Capitalize);
    font.setWeight(QFont::Black);

    for(int i = 0 ; i < ui->chauffeurTable->rowCount() ; i++){ // Going through rows
        ui->chauffeurTable->setItem(i,0,new QTableWidgetItem(locale.toString(buffer,"dddd"))); // Writing the day in first column
        ui->tourneeTable->setItem  (i,0,new QTableWidgetItem(locale.toString(buffer,"dddd")));   // In both tables
        ui->chauffeurTable->item(i,0)->setFont(font);
        ui->tourneeTable->item  (i,0)->setFont(font);
        QBrush color;
        if (buffer.dayOfWeek()>5){ // if it's a weekend day
            color = Qt::yellow;
        } else {
            color = Qt::white;
        }
        for(int j = 0 ; j < ui->tourneeTable->columnCount() ; j++){ // Filling color in tournee table
            if(ui->tourneeTable->item(i,j) == nullptr){ // if no item is set
                ui->tourneeTable->setItem(i,j,new QTableWidgetItem());
            }
            ui->tourneeTable->item(i,j)->setBackground(color);
        }
        for(int j = 0 ; j < ui->chauffeurTable->columnCount() ; j++){ // Filling colors in chauff table
            if(ui->chauffeurTable->item(i,j) == nullptr){
                ui->chauffeurTable->setItem(i,j,new QTableWidgetItem());
            }
            ui->chauffeurTable->item(i,j)->setBackground(color);
        }
        buffer = buffer.addDays(1);
    }
}

void MainWindow::update_chauffeurs(QDate& from_date, QDate& to_date){
    //get dates
    QStringList labels;
    drivers.clear();
    QDate buffer = from_date;
    // Fill the labels string list
    for(int i = 0 ; i < from_date.daysTo(to_date)+1; i++){
        labels << buffer.toString("dd/MM/yyyy");
        buffer = buffer.addDays(1);
    }

    // Create the number of row needed and naming them with dates
    ui->chauffeurTable->setRowCount(from_date.daysTo(to_date)+1);
    ui->chauffeurTable->setVerticalHeaderLabels(labels);

    QSqlQuery query = QSqlQuery(maindb);

    // COLUMNS
    // Retrieving column labels
    query.exec("SELECT surname, name, full_name FROM Chauffeurs");
    labels.clear();
    int colNum = 1;
    labels << "Jour";
    while(query.next()){
        labels  << query.value(0).toString() + " " + query.value(1).toString()[0] + ".";
        drivers << query.value(2).toString();
        colNum++;
    }

    ui->chauffeurTable->setColumnCount(colNum);
    ui->chauffeurTable->setHorizontalHeaderLabels(labels);
}

void MainWindow::update_tournees(QDate& from_date, QDate& to_date){

    //get dates
    QStringList labels;
    QDate buffer = from_date;
    // Fill the labels string list
    for(int i = 0 ; i < from_date.daysTo(to_date)+1; i++){
        char sbuffer[11];
        sprintf(sbuffer, "%02d/%02d/%04d",buffer.day(), buffer.month(), buffer.year() );
        labels << sbuffer;
        buffer = buffer.addDays(1);
    }

    // Create the number of row needed and naming them with dates
    ui->tourneeTable->setRowCount(from_date.daysTo(to_date)+1);
    ui->tourneeTable->setVerticalHeaderLabels(labels);

    QSqlQuery query = QSqlQuery(maindb);

    // COLUMNS
    // Retrieving column labels
    labels.clear();
    query.exec("SELECT name FROM Tournees");
    int colNum = 1;
    labels << "Jour";
    while(query.next()){
        labels  << query.value(0).toString();
        colNum++;
    }


    ui->tourneeTable->setColumnCount(colNum);
    ui->tourneeTable->setHorizontalHeaderLabels(labels);
}

void MainWindow::update_data_chauff(QDate &from_date){
    QSqlQuery query = QSqlQuery(maindb);

    for (int i = 0 ; i < ui->chauffeurTable->rowCount() ; i++){
        QDate date = from_date.addDays(i);
        for (int j = 1 ; j < ui->chauffeurTable->columnCount() ; j++){
            QString driver = drivers[j-1];

            query.prepare("SELECT tour FROM Events WHERE date = :date AND driver = :driver");
            query.bindValue(":date", date.toString(Qt::ISODate));
            query.bindValue(":driver", driver);

            if(!query.exec()){
                QMessageBox::critical(this, "SQLError", query.lastError().text());
            }

            if (query.next()){
                ui->chauffeurTable->item(i,j)->setTextAlignment(Qt::AlignCenter);
                ui->chauffeurTable->item(i,j)->setText(query.value(0).toString());
            }
        }
    }
}

void MainWindow::update_data_tour(QDate &from_date){

}

void MainWindow::update_tables(){
    QDate from_date = ui->fromDateEdit->date();
    QDate to_date = ui->toDateEdit->date();

    update_chauffeurs(from_date, to_date);
    update_tournees(from_date, to_date);

    yellow_weekends(from_date);

    update_data_chauff(from_date);
}

void MainWindow::on_fromDateEdit_userDateChanged(const QDate &date)
{
    update_tables();
}

void MainWindow::on_toDateEdit_userDateChanged(const QDate &date)
{
    update_tables();
    // ui->fromDateEdit->setMinimumDate(ui->toDateEdit->date().addDays(-60));
}

void MainWindow::on_tourneeTable_doubleClicked(const QModelIndex &index)
{
    QDate from_date = ui->fromDateEdit->date();
    qDebug() << "double clicked";

    AddEvent* addev = new AddEvent(this);
    addev->set_default_date(from_date.addDays(index.row()));

    QString tour = ui->tourneeTable->horizontalHeaderItem(index.column())->text();
    addev->set_tour(tour);

    addev->exec();

    update_tables();
}


void MainWindow::on_chauffeurTable_doubleClicked(const QModelIndex &index)
{
    QDate from_date = ui->fromDateEdit->date();
    qDebug() << "double clicked";

    AddEvent* addev = new AddEvent(this);
    addev->set_default_date(from_date.addDays(index.row()));

    QString driver = drivers[index.column() - 1];

    addev->set_driver(driver);
    addev->exec();

    update_tables();
}



