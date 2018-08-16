#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>

#include "adminwindow.h"
#include "mainwindow.h"
#include "db.h"
#include "registrationwindow.h"


namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = 0);
    ~AuthorizationWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::AuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
