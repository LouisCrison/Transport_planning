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
