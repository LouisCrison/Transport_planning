#include "displaytournee.h"
#include "ui_displaytournee.h"

DisplayTournee::DisplayTournee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayTournee)
{
    ui->setupUi(this);
    MainWindow* mw = qobject_cast<MainWindow*>(parent);
    maindb = mw->getdb();

    update_table();
}

DisplayTournee::~DisplayTournee()
{
    delete ui;
}

void DisplayTournee::update_table(){

    QSqlTableModel* model = new QSqlTableModel(this,maindb);

    model->setTable("Tournees");
    model->select();

    ui->dispTourTable->setModel(model);

    ui->dispTourTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void DisplayTournee::on_addTourBtn_clicked()
{
    AddTournee* addTour = new AddTournee(this);
    addTour->exec();
}

void DisplayTournee::on_dltTourBtn_clicked()
{
    QString name;
    QSqlQuery query = QSqlQuery(maindb);

    int row = ui->dispTourTable->selectionModel()->selectedRows().first().row();


    name = ui->dispTourTable->model()->index(row, 0).data().toString();

    query.prepare("DELETE FROM Tournees WHERE nom = :name");
    query.bindValue(":name", name);
    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR", query.lastError().text());
    }

    update_table();
}
