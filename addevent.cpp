#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

void AddEvent::setDefaultDate(QDate date){
    ui->dateEdit->setDate(date);
}

AddEvent::~AddEvent()
{
    delete ui;
}
