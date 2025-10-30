#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addchauffeur.h"
#include "displaychauffeurs.h"
#include "displaycamions.h"
#include "displaytournee.h"
#include "displayclient.h"
#include "addevent.h"

#include <iostream>
#include <string>

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDate>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase getdb();

private slots:
    void on_chauffeursButton_clicked();

    void on_camionsButton_clicked();

    void on_tourneesButton_clicked();

    void on_fromDateEdit_userDateChanged(const QDate &date);

    void on_toDateEdit_userDateChanged(const QDate &date);

    void on_tourneeTable_doubleClicked(const QModelIndex &index);

    void on_chauffeurTable_doubleClicked(const QModelIndex &index);

    void on_clientsButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase maindb;
    void create_tables();
    void update_tables();
    void yellow_weekends(QDate& from_date);
    void update_tournees(QDate& from_date, QDate& to_date);
    void update_chauffeurs(QDate& from_date, QDate& to_date);
};
#endif // MAINWINDOW_H
