#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"


AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::on_pushButton_clicked()
{
    DB *database = new DB();
    if (!(database->connect(ui->lineEdit->text(), ui->lineEdit_2->text()))) {
        QMessageBox *box = new QMessageBox();
        if (box) {
            box->setText("Соединение не было установлено, повторите попытку");
            box->setDefaultButton(QMessageBox::Save);
            box->exec();
            delete box;
        }
    }
    else {
        if (database->checkAdmin()) {
            AdminWindow * w = new AdminWindow(database);
            w->show();
            this->close();
        } else {
            MainWindow * w = new MainWindow(database);
            w->show();
            this->close();
        }
    }
}

void AuthorizationWindow::on_pushButton_2_clicked()
{
    RegistrationWindow *w = new RegistrationWindow(*this);
    this->hide();
    w->show();
}
