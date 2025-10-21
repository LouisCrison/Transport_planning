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

    void on_idChauffCombo_currentIndexChanged(const QString &arg1);

private:
    Ui::AddTournee *ui;

    QSqlDatabase maindb;

    void fill_combo_box();
};

#endif // ADDTOURNEE_H
