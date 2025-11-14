#include "displaychauffeurs.h"
#include "ui_displaychauffeurs.h"

DisplayChauffeurs::DisplayChauffeurs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayChauffeurs)
{
    ui->setupUi(this);

    MainWindow *mw = qobject_cast<MainWindow*>(parent);
    maindb = mw->getdb();
    update_table();
}

DisplayChauffeurs::~DisplayChauffeurs()
{
    delete ui;
}


void DisplayChauffeurs::update_table() {

    QSqlTableModel* model = new QSqlTableModel(this,maindb);

    model->setTable("Chauffeurs");
    model->select();

    ui->chauffTable->setModel(model);
}

void DisplayChauffeurs::on_AddButton_clicked()
{
    AddChauffeur* addChauff = new AddChauffeur(this);
    addChauff->exec();
    update_table();
}

void DisplayChauffeurs::on_DeleteButton_clicked()
{
    int result = QMessageBox::warning(this, "Supprimer une Tournée", "Voulez vous vraiment supprimer cette tournée?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::No){
        return;
    }

    QSqlQuery query = QSqlQuery(maindb);

    QModelIndexList selection = ui->chauffTable->selectionModel()->selectedRows();

    if (selection.size() == 0){
        return;
    }
    int row = selection.first().row();


    QString name = ui->chauffTable->model()->index(row, 0).data().toString();
    QString surname = ui->chauffTable->model()->index(row, 1).data().toString();


    query.prepare("DELETE FROM Chauffeurs WHERE ((name = :name) AND (surname = :surname))");
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR deleting", query.lastError().text());
    }
    qDebug() << "row deleted : " << query.numRowsAffected();

    update_table();
}
