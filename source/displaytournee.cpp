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

    QSqlRelationalTableModel* model = new QSqlRelationalTableModel(this,maindb);
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    model->setTable("Tournees");
    model->setRelation(model->fieldIndex("driver"), QSqlRelation("Chauffeurs", "full_name", "full_name"));
    model->select();


    ui->dispTourTable->setModel(model);
    ui->dispTourTable->setItemDelegate(new QSqlRelationalDelegate(ui->dispTourTable));

    ui->dispTourTable->setItemDelegateForColumn(3, new TourneesRelationalDelegate(this));

    ui->dispTourTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void DisplayTournee::on_addTourBtn_clicked()
{
    AddTournee* addTour = new AddTournee(this);
    addTour->exec();
    update_table();
}

void DisplayTournee::on_dltTourBtn_clicked()
{
    int result = QMessageBox::warning(this, "Supprimer une Tournée", "Voulez vous vraiment supprimer cette tournée?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No){
        return;
    }


    QString name;
    QSqlQuery query = QSqlQuery(maindb);

    QModelIndexList selection = ui->dispTourTable->selectionModel()->selectedRows();
    if(selection.size() == 0){
        return;
    }
    int row = selection.first().row();


    name = ui->dispTourTable->model()->index(row, 0).data().toString();

    query.prepare("DELETE FROM Tournees WHERE name = :name");
    query.bindValue(":name", name);
    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR", query.lastError().text());
    }

    update_table();
}


