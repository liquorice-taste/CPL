#include "db.h"

DB::DB() {

}

DB::~DB(){
    db->close();
    db->removeDatabase(db->defaultConnection);
}

bool DB::connect(QString &login, QString &pswd) {
    db = new QSqlDatabase();
    db->addDatabase("QPSQL");
    db->setDatabaseName("air");
    db->setUserName(login);
    db->setPassword(pswd);
    db->setHostName("localhost");
    db->setPort(5432);
    return(db->open());
}

bool DB::checkAdmin(){
    QSqlQuery q = QSqlQuery(*db);
    q.prepare("select check_admin();");
    q.exec();
    q.next();
    return q.value(0).toBool();
}

QSqlDatabase *DB::getdb(){
    return this->db;
}


void DB::debugLastError(){
    qDebug() << db->lastError().text();
}
