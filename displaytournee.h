#ifndef DISPLAYTOURNEE_H
#define DISPLAYTOURNEE_H

#include "mainwindow.h"
#include "addtournee.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlTableModel>

namespace Ui {
class DisplayTournee;
}

class DisplayTournee : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayTournee(QWidget *parent = nullptr);
    ~DisplayTournee();
    void update_table();

private slots:
    void on_addTourBtn_clicked();

    void on_dltTourBtn_clicked();

private:
    Ui::DisplayTournee *ui;
    QSqlDatabase maindb;
};

#endif // DISPLAYTOURNEE_H
