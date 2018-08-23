#ifndef BOARDINGPASSWINDOW_H
#define BOARDINGPASSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QRadioButton>
#include <QWidget>
#include <QScrollArea>
#include <QButtonGroup>
#include <QList>
#include "qchar.h"
#include "db.h"

namespace Ui {
class BoardingPassWindow;
}

class BoardingPassWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardingPassWindow(QMainWindow *w, DB *base, int flight_id, QString ticket_no, QString fare_condition,  QWidget *parent = 0);
    ~BoardingPassWindow();

private slots:

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    DB *db;
    QMainWindow *mainwin;
    QButtonGroup *bgr;
    QList<QRadioButton*> *bl;
    int fl_id;
    QString tick_no;
    Ui::BoardingPassWindow *ui;
    QWidget *widget;
};

#endif // BOARDINGPASSWINDOW_H
