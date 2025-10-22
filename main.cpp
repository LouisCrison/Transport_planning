#include <iostream>

#include "mainwindow.h"

#include <string>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow(nullptr);
    w->show();
    return a.exec();
}
