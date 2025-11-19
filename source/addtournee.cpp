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

    QString name    = ui->nameLine->text();
    qint32 price    = ui->priceLine->text().toInt();
    QVariant driver = ui->chauffCombo->currentData();
    QString client  = ui->clientCombo->currentText();
    QVariant truck  = ui->truckCombo->currentData();


    qDebug() << "name : "   << name;
    qDebug() << "price : "  << price;
    qDebug() << "camion : " << truck.toString();
    qDebug() << "driver : " << driver.toString();



    query.prepare("INSERT INTO Tournees (name, client, price, driver, truck) VALUES (:name, :client, :price, :driver, :truck)");
    query.bindValue(":name", name);
    query.bindValue(":client", client);
    query.bindValue(":price", price);
    query.bindValue(":driver",driver);
    query.bindValue(":truck",truck);

    if(!query.exec()){
        QMessageBox::critical(this, "SQLERROR", query.lastError().text());
        return;
    }

    this->close();
}



void AddTournee::fill_combo_box(){

    fill_driver_combo_box();
    fill_client_combo_box();
    fill_truck_combo_box();
}

void AddTournee::fill_driver_combo_box(){

    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT full_name FROM Chauffeurs");

    int i = 0;
    ui->chauffCombo->insertItem(i, "<aucun>", QVariant());

    while(query.next()){
        i++;
        ui->chauffCombo->insertItem(i,query.value(0).toString(), QVariant(query.value(0).toString()));
    }


}

void AddTournee::fill_client_combo_box(){
    QStringList items;
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT name FROM Clients");

    while(query.next()){
        items << query.value(0).toString();
    }

    ui->clientCombo->insertItems(0,items);
}

void AddTournee::fill_truck_combo_box(){

    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT * FROM Trucks");

    int i = 0;
    ui->truckCombo->insertItem(i, "<aucun>" , QVariant());

    while(query.next()){
        i++;
        ui->truckCombo->insertItem(i, query.value(0).toString(), QVariant(query.value(0).toString()));
    }
}

void AddTournee::on_cancelBtn_clicked()
{
    this->close();
}

