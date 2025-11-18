#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseSingleton
{
public:

    static DatabaseSingleton& get_instance();

    DatabaseSingleton(DatabaseSingleton& other) = delete; // copy constructor
    DatabaseSingleton& operator=(const DatabaseSingleton&) = delete;

    QSqlDatabase& get_db();

private:
    DatabaseSingleton();  // private constructor

    QSqlDatabase main_db;

};

#endif // DATABASESINGLETON_H
