#include "addchauffeur.h"
#include "ui_addchauffeur.h"

addChauffeur::addChauffeur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addChauffeur)
{
    ui->setupUi(this);
}

addChauffeur::~addChauffeur()
{
    delete ui;
}
