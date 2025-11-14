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
        list << query.value("surname").toString() + " " + query.value("name").toString()[0] + ".";
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

void AddEvent::set_driver(QString driver){ // Driver given in format "name surname"
    QSqlQuery query = QSqlQuery(maindb);
    qDebug() << "driver : " << driver;


    query.prepare("SELECT name, surname FROM Chauffeurs WHERE name || ' ' || surname = :driver");
    query.bindValue(":driver", driver);
    query.exec();

    qDebug() << query.size();
    query.next();


    QString full_name = query.value(1).toString() + " " + query.value(0).toString()[0] + ".";


    ui->driverCombo->setCurrentText(full_name); // Needs to be passed as "surname n."
    qDebug() << "setting driver to " << full_name;
    return;
}


void AddEvent::set_tour(QDate date){
    ui->dateEdit->setDate(date);
}


AddEvent::~AddEvent()
{
    delete ui;
}
