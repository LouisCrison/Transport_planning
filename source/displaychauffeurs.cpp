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
    int id;
    QSqlQuery query = QSqlQuery(maindb);

    int row = ui->chauffTable->selectionModel()->selectedRows().first().row();


    id = ui->chauffTable->model()->index(row, 0).data().toInt();


    query.prepare("DELETE FROM Chauffeurs WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR", query.lastError().text());
    }

    update_table();
}
