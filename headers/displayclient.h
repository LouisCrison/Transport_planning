#ifndef DISPLAYCLIENT_H
#define DISPLAYCLIENT_H

#include "addclient.h"
#include "databasesingleton.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class DisplayClient;
}

class DisplayClient : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayClient(QWidget *parent = nullptr);
    ~DisplayClient();

private slots:
    void on_addClientBtn_clicked();



    void on_deleteClientBtn_clicked();

private:
    Ui::DisplayClient *ui;

    void update_table();

    QSqlDatabase main_db;
};

#endif // DISPLAYCLIENT_H
