#ifndef DISPLAY_CHAUFFEURS_H
#define DISPLAY_CHAUFFEURS_H

#include "mainwindow.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class DisplayChauffeurs;
}

class DisplayChauffeurs : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayChauffeurs(QWidget *parent = nullptr);
    ~DisplayChauffeurs();



private slots:
    void on_AddButton_clicked();

    void on_DeleteButton_clicked();

private:
    Ui::DisplayChauffeurs *ui;
    QSqlDatabase maindb;
    void update_table();
};


#endif // DISPLAY_CHAUFFEURS_H
