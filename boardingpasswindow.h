#ifndef BOARDINGPASSWINDOW_H
#define BOARDINGPASSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QRadioButton>
#include <QWidget>
#include <QScrollArea>
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
    //QList<*QCheckBox> checkBoxList;
    DB *db;
    QMainWindow *mainwin;
    QButtonGroup *bgr;
    int fl_id;
    QString tick_no;
    Ui::BoardingPassWindow *ui;
};

#endif // BOARDINGPASSWINDOW_H
