
#include "databasesingleton.h"


DatabaseSingleton::DatabaseSingleton() {
    main_db = QSqlDatabase::addDatabase("QSQLITE");
    main_db.setDatabaseName("main_database.db");
    main_db.open();
}


QSqlDatabase& DatabaseSingleton::get_db(){
    return main_db;
}


DatabaseSingleton& DatabaseSingleton::get_instance(){
    static DatabaseSingleton instance = DatabaseSingleton();
    return instance;
}
