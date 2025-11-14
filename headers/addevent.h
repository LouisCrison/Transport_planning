#ifndef ADDEVENT_H
#define ADDEVENT_H

#include "databasesingleton.h"

#include <QDialog>
#include <QDate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent = nullptr);
    ~AddEvent();



    void set_default_date(QDate date);
    void set_driver(QString driver);
    void set_tour(QDate date);

private:
    Ui::AddEvent *ui;

    QSqlDatabase maindb;

    void fill_combo_boxes();
    void fill_driver_combo();
    void fill_truck_combo();
    void fill_tour_combo();

};

#endif // ADDEVENT_H
