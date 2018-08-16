#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"
#include "purchasewindow.h"
#include "boardingpasswindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QTextCodec>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QPainter>
#include <QFileDialog>
#include <QSaveFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DB * base, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_4_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

private:
    DB *db;
    Ui::MainWindow *ui;
    QString current_fc;
};

#endif // MAINWINDOW_H
