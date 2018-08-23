#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlTableModel>
#include <QKeyEvent>

#include "db.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(DB *base, QWidget *parent = 0);
    ~AdminWindow();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

private:
    void updateTableModel(QString tableName, QSqlTableModel *model);
    QSqlTableModel *airports;
    QSqlTableModel *aircrafts;
    QSqlTableModel *flights;
    QSqlTableModel *tickets;
    QSqlTableModel *seats;
    QSqlTableModel *boarding_passes;

    DB *db;
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
