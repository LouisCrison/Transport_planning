#include "addtournee.h"
#include "ui_addtournee.h"

AddTournee::AddTournee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTournee)
{
    ui->setupUi(this);
    MainWindow* mw = qobject_cast<MainWindow*>(parent->parent());
    maindb = mw->getdb();

    fill_combo_box();
}

AddTournee::~AddTournee()
{
    delete ui;
}


void AddTournee::on_addTourBtn_clicked()
{
    QSqlQuery query = QSqlQuery(maindb);

    QString name = ui->nameLine->text();
    qint32 price = ui->priceLine->text().toInt();
    QString driver = ui->chauffCombo->currentText();
    QString client = ui->clientCombo->currentText();
    QString truck = ui->truckCombo->currentText();


    qDebug() << "name : " << name;
    qDebug() << "price : " << price;
    qDebug() << "camion : " << truck;
    qDebug() << "driver : " << driver;

    query.prepare("INSERT INTO Tournees (name, client, price, driver, truck) VALUES (:name, :client, :price, :driver, :truck)");
    query.bindValue(":name", name);
    query.bindValue(":client", client);
    query.bindValue(":price", price);
    query.bindValue(":driver", driver);
    query.bindValue(":truck", truck);

    if(!query.exec()){
        QMessageBox::critical(this, "SQLERROR", query.lastError().text());
    }

    this->close();
}



void AddTournee::fill_combo_box(){

    fill_driver_combo_box();
    fill_client_combo_box();
    fill_truck_combo_box();
}

void AddTournee::fill_driver_combo_box(){
    QStringList items;
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT full_name FROM Chauffeurs");
    items << "";

    while(query.next()){
        items << query.value(0).toString();
    }

    ui->chauffCombo->insertItems(0,items);
}

void AddTournee::fill_client_combo_box(){
    QStringList items;
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT name FROM Clients");
    ui->clientCombo->insertItem(0,"");

    while(query.next()){
        items << query.value(0).toString();
    }

    ui->clientCombo->insertItems(1,items);
}

void AddTournee::fill_truck_combo_box(){
    QStringList items;
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT * FROM Trucks");
    ui->truckCombo->insertItem(0,"");

    while(query.next()){
        items << query.value(0).toString();
    }

    ui->truckCombo->insertItems(1,items);
}

void AddTournee::on_cancelBtn_clicked()
{
    this->close();
}

