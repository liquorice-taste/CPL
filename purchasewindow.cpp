#include "purchasewindow.h"
#include "ui_purchasewindow.h"

PurchaseWindow::PurchaseWindow(QMainWindow * m, DB *base, QString flight_id, QString fare_condition, QString price, QWidget *parent) :
    QMainWindow(parent),
    mainwin(m),
    db(base),
    ui(new Ui::PurchaseWindow)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::CustomizeWindowHint );
    this->setAttribute(Qt::WA_DeleteOnClose);

    QSqlQuery q = QSqlQuery(*db->getdb());
    q.prepare("select * from flight_status_by_id(:fl)");
    q.bindValue(0, flight_id);
    q.exec();
    while (q.next()) {
        ui->LB_aipportdep->setText(q.value(4).toString());
        ui->LB_aipportarr->setText(q.value(5).toString());
        ui->LB_timearr->setText(q.value(3).toString());
        ui->LB_timedep->setText(q.value(2).toString());
        ui->LB_flightid->setText(flight_id);
        ui->LB_farecondition->setText(fare_condition);
        ui->LB_price->setText(price);
    }
    QRegExp re("^[а-яА-ЯёЁa-zA-Z0-9]+$");
    QRegExpValidator *validator = new QRegExpValidator(re, this);
    ui->LE_name->setValidator(validator);
    ui->LE_surname->setValidator(validator);
}

PurchaseWindow::~PurchaseWindow()
{
    delete ui;
}

void PurchaseWindow::on_pushButton_clicked()
{
    QSqlQuery q = QSqlQuery();
    q.prepare("select buy_ticket(:fl_id, :pass_ser, :pass_num, :name, :surname, :price, :fc)");
    q.bindValue(0, ui->LB_flightid->text());
    q.bindValue(1, ui->LE_passseries->text());
    q.bindValue(2, ui->LE_passnum->text());
    q.bindValue(3, ui->LE_name->text());
    q.bindValue(4, ui->LE_surname->text());
    q.bindValue(5, ui->LB_price->text());
    q.bindValue(6, ui->LB_farecondition->text());
    if (q.exec()){
        ui->stackedWidget->setCurrentIndex(1);
    }

}

void PurchaseWindow::on_pushButton_2_clicked()
{
    this->close();
    mainwin->show();
}

void PurchaseWindow::on_PurchaseWindow_destroyed()
{
}

void PurchaseWindow::on_pushButton_3_clicked()
{
    this->close();
    mainwin->show();
}
