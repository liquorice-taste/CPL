#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQuery>


#include <db.h>

namespace Ui {
class PurchaseWindow;
}

class PurchaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PurchaseWindow(QMainWindow * m, DB *base, QString flight_id, QString fare_condition, QString price, QWidget *parent = 0);
    ~PurchaseWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_PurchaseWindow_destroyed();

    void on_pushButton_3_clicked();

private:
    QMainWindow *mainwin;
    DB * db;
    Ui::PurchaseWindow *ui;
};

#endif // PURCHASEWINDOW_H
