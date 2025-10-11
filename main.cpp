#include <iostream>

#include "mainwindow.h"

#include <string>
#include <QApplication>


int main(int argc, char *argv[])
{
    std::cout << argv[1] << std::endl;
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow(nullptr,argv[1]);
    w->show();
    return a.exec();
}
