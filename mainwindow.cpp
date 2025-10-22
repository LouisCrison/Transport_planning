#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    std::cout << "drivers :" << std::endl;
//    qDebug() << QSqlDatabase::drivers();

    maindb = QSqlDatabase::addDatabase("QSQLITE");
    maindb.setDatabaseName("main_database.db");

    if(!maindb.open()){
        QMessageBox::critical(this,"Error opening database",maindb.lastError().text());
        return;
    }
    create_tables();
    update_tables();
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
    update_tables();
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
    for(int i = 0 ; i < ui->tourneeTable->rowCount() ; i++){
        ui->tourneeTable->setItem(i,0,new QTableWidgetItem(locale.toString(buffer,"dddd")));
        if (buffer.dayOfWeek()>5){
            for(int j = 0 ; j < ui->tourneeTable->columnCount() ; j++){
                if(ui->tourneeTable->item(i,j) == nullptr){
                    ui->tourneeTable->setItem(i,j,new QTableWidgetItem());
                }
                ui->tourneeTable->item(i,j)->setBackground(Qt::yellow);
            }
        }
        buffer = buffer.addDays(1);
    }

    buffer = from_date;
    for(int i = 0 ; i < ui->chauffeurTable->rowCount() ; i++){
        ui->chauffeurTable->setItem(i,0,new QTableWidgetItem(locale.toString(buffer,"dddd")));
        if (buffer.dayOfWeek()>5){
            for(int j = 0 ; j < ui->tourneeTable->columnCount() ; j++){
                if(ui->chauffeurTable->item(i,j) == nullptr){
                    ui->chauffeurTable->setItem(i,j,new QTableWidgetItem());
                }
                ui->chauffeurTable->item(i,j)->setBackground(Qt::yellow);
            }
        }
        buffer = buffer.addDays(1);
    }
}

void MainWindow::update_chauffeurs(QDate& from_date, QDate& to_date){
    //get dates
    QStringList labels;
    QDate buffer = from_date;
    // Fill the labels string list
    for(int i = 0 ; i < from_date.daysTo(to_date)+1; i++){
        char sbuffer[11];
        sprintf(sbuffer, "%02d/%02d/%04d", buffer.day(), buffer.month(), buffer.year());
        labels << sbuffer;
        buffer = buffer.addDays(1);
    }

    // Create the number of row needed and naming them with dates
    ui->chauffeurTable->setRowCount(from_date.daysTo(to_date)+1);
    ui->chauffeurTable->setVerticalHeaderLabels(labels);

    QSqlQuery query = QSqlQuery(maindb);

    // COLUMNS
    // Retrieving column labels
    query.exec("SELECT nom,prenom FROM Chauffeurs");
    labels.clear();
    int colNum = 1;
    labels << "Jour";
    while(query.next()){
        labels  << query.value(0).toString().append(" ").append(query.value(1).toString());
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
    query.exec("SELECT nom FROM Tournees");
    int colNum = 1;
    labels << "Jour";
    while(query.next()){
        labels  << query.value(0).toString();
        colNum++;
    }


    ui->tourneeTable->setColumnCount(colNum);
    ui->tourneeTable->setHorizontalHeaderLabels(labels);
}

void MainWindow::update_tables(){
    QDate from_date = ui->fromDateEdit->date();
    QDate to_date = ui->toDateEdit->date();

    update_chauffeurs(from_date, to_date);
    update_tournees(from_date, to_date);

    yellow_weekends(from_date);
}

void MainWindow::on_fromDateEdit_userDateChanged(const QDate &date)
{
    update_tables();
}

void MainWindow::on_toDateEdit_userDateChanged(const QDate &date)
{
    update_tables();
}
