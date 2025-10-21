#include "displaycamions.h"
#include "ui_displaycamions.h"

DisplayCamions::DisplayCamions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayCamions)
{
    ui->setupUi(this);
}

DisplayCamions::~DisplayCamions()
{
    delete ui;
}
