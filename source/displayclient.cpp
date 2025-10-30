#include "displayclient.h"
#include "ui_displayclient.h"

DisplayClient::DisplayClient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisplayClient)
{
    ui->setupUi(this);

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();
    main_db = instance.get_db();

    update_table();
}

DisplayClient::~DisplayClient()
{
    delete ui;
}



void DisplayClient::on_addClientBtn_clicked()
{
    AddClient* addC = new AddClient();
    addC->exec();
    delete(addC);

    update_table();
}


void DisplayClient::on_deleteClientBtn_clicked()
{
    int result = QMessageBox::warning(this, "Supprimer un Client", "Voulez vous vraiment supprimer ce client ?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No){
        return;
    }

    int row = ui->clientTableView->selectionModel()->selectedRows().first().row();

    QSqlQuery* query =new QSqlQuery(main_db);

    QString name = ui->clientTableView->model()->index(row,0).data().toString();

    query->prepare("DELETE FROM Clients WHERE name = :name");
    query->bindValue(":name", name);
    if(!query->exec()){
        QMessageBox::critical(this, "SQL ERROR", query->lastError().text());
    }

    delete(query);

    update_table();
}


void DisplayClient::update_table(){
    QSqlTableModel* model = new QSqlTableModel(this, main_db);

    model->setTable("Clients");
    model->select();

    ui->clientTableView->setModel(model);
}
