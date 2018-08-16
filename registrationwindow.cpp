#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QMainWindow &mainwin, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow),
    win(mainwin)
{
    ui->setupUi(this);
    if (!regdb.connect("air_reg", "123")) {
        regdb.debugLastError();
    };
    QRegExp re("^[a-zA-Z][a-zA-Z0-9-_\\.]{1,20}$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    ui->loginEdit->setValidator(validator);
    ui->pswdEdit1->setValidator(validator);
    ui->pswdEdit2->setValidator(validator);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_clicked()
{
    if (ui->pswdEdit1->text() == ui->pswdEdit2->text()){
    QSqlQuery *q = new QSqlQuery(*regdb.getdb());
    q->prepare("select add_user(:login, :pswd);");
    q->bindValue(0, ui->loginEdit->text());
    q->bindValue(1, ui->pswdEdit1->text());
    if (q->exec()) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
    }
    } else {
        QMessageBox *mb = new QMessageBox();
        mb->setText("Пароли не совпадают");
        mb->setVisible(true);
    }
}

void RegistrationWindow::on_pushButton_2_clicked()
{
    //delete(regdb);
    this->close();
    win.show();
}

void RegistrationWindow::on_pushButton_4_clicked()
{
    //delete(regdb);
    this->close();
    win.show();
}
