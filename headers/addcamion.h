#ifndef ADDCAMION_H
#define ADDCAMION_H

#include "databasesingleton.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class AddCamion;
}

class AddCamion : public QDialog
{
    Q_OBJECT

public:
    explicit AddCamion(QWidget *parent = nullptr);
    ~AddCamion();

private slots:
    void on_addTruckBtn_clicked();

private:
    Ui::AddCamion *ui;

    QSqlDatabase maindb;
};

#endif // ADDCAMION_H
