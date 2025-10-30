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

    // qDebug() << "name : " << name;
    // qDebug() << "price : " << price;
    // qDebug() << "camion : " << camion;

    // query.prepare("INSERT INTO Tournees VALUES (:name, :client, :price, :chauff_name, :chauff_surname, :camion)");
    // query.bindValue(":name", name);
    // query.bindValue(":client", client);
    // query.bindValue(":price", price);
    // query.bindValue(":chauff_name", chauff_name);
    // query.bindValue(":chauff_surname", chauff_surname);
    // query.bindValue(":camion", camion);

    // if(!query.exec()){
    //     QMessageBox::critical(this, "SQLERROR", query.lastError().text());
    // }

    this->close();

    qDebug() << "clicked";
}

void AddTournee::on_idChauffCombo_currentIndexChanged(const QString &arg1)
{

}

void AddTournee::fill_combo_box(){

    QStringList items;
    QSqlQuery query = QSqlQuery(maindb);

    query.exec("SELECT * FROM Chauffeurs");
    ui->idChauffCombo->insertItem(0,"N/A");

    while(query.next()){
        items << query.value(1).toString().append(" ").append(query.value(2).toString());
    }

    ui->idChauffCombo->insertItems(1,items);
}
