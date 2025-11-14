#include "displaycamions.h"
#include "ui_displaycamions.h"

DisplayCamions::DisplayCamions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayCamions)
{
    ui->setupUi(this);

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();
    main_db = instance.get_db();

    update_table();

}

DisplayCamions::~DisplayCamions()
{
    delete ui;
}

void DisplayCamions::update_table(){

    QSqlTableModel* model = new QSqlTableModel(this, main_db);
    QSqlQuery query = QSqlQuery(main_db);

    query.exec("SELECT * FROM Trucks");

    while(query.next()){
        qDebug() << query.value(0);
    }

    model->setTable("Trucks");
    model->select();

    ui->dispCamionsTable->setModel(model);
}

void DisplayCamions::on_addCamionBtn_clicked()
{
    AddCamion* addT = new AddCamion(this);
    addT->exec();
    update_table();
}


void DisplayCamions::on_dltCamionBtn_clicked()
{

    int result = QMessageBox::warning(this, "Supprimer un Camion", "Voulez vous vraiment supprimer ce camion?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No){
        return;
    }

    QModelIndexList selection = ui->dispCamionsTable->selectionModel()->selectedRows();
    if (selection.size() == 0){
        qDebug() << "please select a row";
        return;
    }
    int row = selection.first().row();

    QString immat = ui->dispCamionsTable->model()->index(row,0).data().toString();

    QSqlQuery query = QSqlQuery(main_db);

    query.prepare("DELETE FROM Trucks WHERE immat = :immat");
    query.bindValue(":immat", immat);

    if (!query.exec()){
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
    }
    update_table();
}

