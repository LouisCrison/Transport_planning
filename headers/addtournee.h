#ifndef ADDTOURNEE_H
#define ADDTOURNEE_H

#include "mainwindow.h"

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class AddTournee;
}

class AddTournee : public QDialog
{
    Q_OBJECT

public:
    explicit AddTournee(QWidget *parent = nullptr);
    ~AddTournee();

private slots:
    void on_addTourBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AddTournee *ui;

    QSqlDatabase maindb;

    void fill_combo_box();
    void fill_driver_combo_box();
    void fill_truck_combo_box();
    void fill_client_combo_box();


};

#endif // ADDTOURNEE_H
