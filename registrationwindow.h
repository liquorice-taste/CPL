#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "db.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QMainWindow &mainwin, QWidget *parent = 0);
    ~RegistrationWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    DB regdb;
    QMainWindow &win;
    Ui::RegistrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
