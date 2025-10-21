#include "displaytournee.h"
#include "ui_displaytournee.h"

DisplayTournee::DisplayTournee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayTournee)
{
    ui->setupUi(this);
}

DisplayTournee::~DisplayTournee()
{
    delete ui;
}
