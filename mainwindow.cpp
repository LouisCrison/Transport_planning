#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addchauffeur.h"

MainWindow::MainWindow(QWidget *parent, std::string city)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    std::cout << "drivers :" << std::endl;
//    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase maindb = QSqlDatabase::addDatabase("QSQLITE");
    maindb.setDatabaseName("main_database.db");

    if(!maindb.open()){
        QMessageBox::critical(this,"Error opening database",maindb.lastError().text());
        return;
    }

    QSqlQuery query;

    if(!query.exec("CREATE TABLE IF NOT EXISTS clients (id INTEGER PRIMARY KEY, nom TEXT, ville TEXT)")) {
         QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
    }

    // Ajouter un client pour tester
    query.exec("DELETE FROM Clients");
    query.exec("INSERT INTO clients (nom, ville) VALUES ('Dupontos de Paris', 'Paris')");
    query.exec("INSERT INTO clients (nom, ville) VALUES ('Dupontos de Tls', 'Toulouse')");
    query.exec("INSERT INTO clients (nom, ville) VALUES ('Dupontos de Amiens', 'Amiens')");
    // Lire les clients
    QString command = "SELECT * FROM clients WHERE ville = '" + QString::fromStdString(city) + "'";
    if(!query.exec(command)){
        qDebug() << "Erreur lecture:" << query.lastError().text();
    } else {
        while(query.next()) {
           qDebug() << query.value(0).toInt()  // id
                    << query.value(1).toString() // nom
                    << query.value(2).toString(); // ville
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    addChauffeur addch;
    addch.show();
}
