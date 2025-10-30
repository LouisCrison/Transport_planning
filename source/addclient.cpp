#include "addclient.h"
#include "ui_addclient.h"

AddClient::AddClient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddClient)
{
    ui->setupUi(this);

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();

    maindb = instance.get_db();
}

AddClient::~AddClient()
{
    delete ui;
}

void AddClient::on_cancelBtn_clicked()
{
    this->close();
}


void AddClient::on_addClientBtn_clicked()
{
    QString name = ui->clientNameEdit->text();
    QString city = ui->clientCityEdit->text();

    QSqlQuery query = QSqlQuery(maindb);

    query.prepare("INSERT INTO Clients VALUES (:name, :city)");

    query.bindValue(":name", name);
    query.bindValue(":city", city);

    if (!query.exec()){
        QMessageBox::critical(this, "SQL ERROR addClient", query.lastError().text());
    }

    this->close();
}

