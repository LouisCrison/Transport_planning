#ifndef DISPLAYCAMIONS_H
#define DISPLAYCAMIONS_H

#include "databasesingleton.h"

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class DisplayCamions;
}

class DisplayCamions : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayCamions(QWidget *parent = nullptr);
    ~DisplayCamions();

private:
    Ui::DisplayCamions *ui;

    void update_table();

    QSqlDatabase main_db;
};

#endif // DISPLAYCAMIONS_H
