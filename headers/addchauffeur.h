#ifndef ADDCHAUFFEUR_H
#define ADDCHAUFFEUR_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QMainWindow>

#include "mainwindow.h"
#include "databasesingleton.h"

namespace Ui {
class AddChauffeur;
}

class AddChauffeur : public QDialog
{
    Q_OBJECT

public:
    explicit AddChauffeur(QWidget *parent = nullptr);
    ~AddChauffeur();

private slots:
    void on_validBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AddChauffeur *ui;
    QSqlDatabase maindb;
};



#endif // ADDCHAUFFEUR_H
