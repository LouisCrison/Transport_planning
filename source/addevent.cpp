#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    ui->setupUi(this);

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();

    maindb = instance.get_db();

    fill_combo_boxes();
}

void AddEvent::fill_combo_boxes(){
    fill_driver_combo();
    fill_tour_combo();
    fill_truck_combo();
    return;
}

void AddEvent::fill_driver_combo(){
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT name, surname FROM Chauffeurs");

    QStringList list;

    list << "";

    while(query.next()){
        list << query.value("surname").toString() + " " + query.value("name").toString();
    }

    ui->driverCombo->insertItems(0, list);
}


void AddEvent::fill_tour_combo(){
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT name FROM Tournees");

    QStringList list;

    list << "";

    while(query.next()){
        list << query.value(0).toString();
    }

    ui->tourCombo->insertItems(0, list);
}

void AddEvent::fill_truck_combo(){
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT immat FROM Trucks");

    QStringList list;

    list << "";

    while(query.next()){
        list << query.value(0).toString();
    }

    ui->truckCombo->insertItems(0, list);
}


void AddEvent::set_default_date(QDate date){
    ui->dateEdit->setDate(date);
}

void AddEvent::set_driver(QString driver){ // Driver given in format "surname name"

    ui->driverCombo->setCurrentText(driver); // Needs to be passed as "surname name"
    qDebug() << "setting driver to " << driver;

    ui->driverCombo->setEnabled(false);

    return;
}


void AddEvent::set_tour(QString tour){
    // ui->dateEdit->setDate(date);
    ui->tourCombo->setCurrentText(tour);
    ui->tourCombo->setEnabled(false);
    return;
}


AddEvent::~AddEvent()
{
    delete ui;
}

void AddEvent::on_validBtn_clicked()
{
    QSqlQuery query = QSqlQuery(maindb);

    QString tour   = ui->tourCombo->currentText();
    QString date   = ui->dateEdit->date().toString(Qt::ISODate);
    QString driver = ui->driverCombo->currentText();
    QString immat  = ui->truckCombo->currentText();

    query.prepare("INSERT INTO Events (tour, date, driver, truck) VALUES (:tour, :date, :driver, :immat)");

    query.bindValue(":tour",   tour);
    query.bindValue(":date",   date);
    query.bindValue(":driver", driver);
    query.bindValue(":immat",  immat);

    if(!query.exec()){
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
    }

    this->close();
}

