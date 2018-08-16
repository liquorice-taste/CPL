#include "boardingpasswindow.h"
#include "ui_boardingpasswindow.h"


BoardingPassWindow::BoardingPassWindow(QMainWindow *w, DB *base, int flight_id, QString ticket_no, QString fare_condition, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BoardingPassWindow),
    db(base),
    mainwin(w),
    fl_id(flight_id),
    tick_no(ticket_no)
{
    ui->setupUi(this);
    bgr = new QButtonGroup();

    QGridLayout* layout = new QGridLayout;
    QSqlQuery *q = new QSqlQuery(*db->getdb());
    q->prepare("select * from seats_for_boarding(:fl_id)");
    q->bindValue(0, flight_id);
    if (q->exec()) {
        while (q->next()) {
            QRadioButton *cb = new QRadioButton(this);
            bgr->addButton(cb);
            if (!q->value(1).toBool() || (fare_condition != q->value(2).toString())) {
                cb->setCheckable(false);
                cb->setStyleSheet("color: rgb(112,128,144);");
            }
            cb->setText(q->value(0).toString());
            QChar str;
            QString s = q->value(0).toString();
            str = q->value(0).toString().back();
            QString sstr = q->value(0).toString().left(s.length() - 1);
            int x = str.unicode() - 65;
            layout->addWidget(cb,x,sstr.toInt(),1,1);
        }
    }

    QWidget* widget = new QWidget;
    widget -> setLayout(layout);
    ui->scrollArea -> setWidget(widget);
}

BoardingPassWindow::~BoardingPassWindow()
{
    delete ui;
}

void BoardingPassWindow::on_pushButton_5_clicked()
{
    this->close();
    mainwin->show();
}

void BoardingPassWindow::on_pushButton_3_clicked()
{
    this->close();
    mainwin->show();
}

void BoardingPassWindow::on_pushButton_4_clicked()
{
    if (bgr->checkedId() != -1) {
        QSqlQuery *q = new QSqlQuery();
        q->prepare("select check_in_for_flight(:seat_no, :fligth_id, :ticket_no)");
        q->bindValue(0, bgr->checkedButton()->text());
        q->bindValue(1, fl_id);
        q->bindValue(2, tick_no);
        if (q->exec()) {
            ui->stackedWidget->setCurrentIndex(1);
        }
    }
}
