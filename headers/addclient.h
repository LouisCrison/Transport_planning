#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include "databasesingleton.h"

#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = nullptr);
    ~AddClient();

private slots:
    void on_cancelBtn_clicked();

    void on_addClientBtn_clicked();

private:
    Ui::AddClient *ui;

    QSqlDatabase maindb;
};

#endif // ADDCLIENT_H
