#include "addchauffeur.h"
#include "ui_addchauffeur.h"

AddChauffeur::AddChauffeur(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AddChauffeur)
{
    ui->setupUi(this);
    MainWindow* mw = qobject_cast<MainWindow*>(parent->parent());
    maindb = mw->getdb();
}

AddChauffeur::~AddChauffeur()
{
    delete ui;
}



void AddChauffeur::on_validBtn_clicked()
{
    QSqlQuery query = QSqlQuery(maindb);

    QString name = ui->nameLine->text();
    QString surname = ui->surnameLine->text();

    query.prepare("INSERT INTO Chauffeurs (name,surname) VALUES (:name,:surname)");
    query.bindValue(":name",name);
    query.bindValue(":surname",surname);

    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR in AddChauffeur",query.lastError().text());
    }

    this->close();
}

void AddChauffeur::on_cancelBtn_clicked()
{
    this->close();
}
