#include "db.h"

DB::DB() {
    qDebug() << "db is created";

}

DB::~DB(){
    qDebug() << "db is deleted";
    db.close();
    db.removeDatabase(db.defaultConnection);
}

bool DB::connect(QString login, QString pswd) {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("air");
    db.setUserName(login);
    db.setPassword(pswd);
    db.setHostName("localhost");
    db.setPort(5432);
    bool op = db.open();
    return(op);
}

bool DB::checkAdmin(){
    QSqlQuery q = QSqlQuery(db);
    q.prepare("select check_admin();");
    q.exec();
    q.next();
    return q.value(0).toBool();
}

QSqlDatabase *DB::getdb(){
    return &this->db;
}


void DB::debugLastError(){
    qDebug() << db.lastError().text();
}
