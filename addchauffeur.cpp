#include "addchauffeur.h"
#include "ui_addchauffeur.h"

AddChauffeur::AddChauffeur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddChauffeur)
{
    ui->setupUi(this);
}

AddChauffeur::~AddChauffeur()
{
    delete ui;
}
