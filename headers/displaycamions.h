#ifndef DISPLAYCAMIONS_H
#define DISPLAYCAMIONS_H

#include "databasesingleton.h"
#include "addcamion.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class DisplayCamions;
}

class DisplayCamions : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayCamions(QWidget *parent = nullptr);
    ~DisplayCamions();

private slots:
    void on_addCamionBtn_clicked();

    void on_dltCamionBtn_clicked();

private:
    Ui::DisplayCamions *ui;

    void update_table();

    QSqlDatabase main_db;
};

#endif // DISPLAYCAMIONS_H
