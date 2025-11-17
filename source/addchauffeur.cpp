#include "addchauffeur.h"
#include "ui_addchauffeur.h"

AddChauffeur::AddChauffeur(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AddChauffeur)
{
    ui->setupUi(this);

    DatabaseSingleton& instance = DatabaseSingleton::get_instance();
    maindb = instance.get_db();
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

    query.prepare("INSERT INTO Chauffeurs (name,surname, full_name) VALUES (:name,:surname, :full_name)");
    query.bindValue(":name",name);
    query.bindValue(":surname",surname);
    query.bindValue(":full_name",surname + ' ' + name);

    if(!query.exec()){
        QMessageBox::critical(this,"SQL ERROR in AddChauffeur",query.lastError().text());
    }

    this->close();
}

void AddChauffeur::on_cancelBtn_clicked()
{
    this->close();
}
