#include "display_chauffeurs.h"
#include "ui_display_chauffeurs.h"

DisplayCHauffeurs::DisplayCHauffeurs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayCHauffeurs)
{
    ui->setupUi(this);
}

DisplayCHauffeurs::~DisplayCHauffeurs()
{
    delete ui;
}
