#include "displayclient.h"
#include "ui_displayclient.h"

DisplayClient::DisplayClient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisplayClient)
{
    ui->setupUi(this);
}

DisplayClient::~DisplayClient()
{
    delete ui;
}



void DisplayClient::on_addClientBtn_clicked()
{
    AddClient* addC = new AddClient();
    addC->exec();
}

