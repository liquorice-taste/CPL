#ifndef DB_H
#define DB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>

class DB
{
public:
    DB();
    ~DB();
    bool connect(QString login, QString pswd);
    bool checkAdmin();
    QSqlDatabase* getdb();
    void debugLastError();
private:
    QSqlDatabase db;
};

#endif // DB_H
