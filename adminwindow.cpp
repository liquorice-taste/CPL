#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(DB *base, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow),
    db(base)
{
    ui->setupUi(this);

    airports = new QSqlTableModel();
    ui->airports_TV->setModel(airports);
    updateTableModel("airports", airports);
    aircrafts = new QSqlTableModel();
    ui->aircrafts_TV->setModel(aircrafts);
    flights = new QSqlTableModel();
    ui->flights_TV->setModel(flights);
    tickets = new QSqlTableModel();
    ui->tickets_TV->setModel(tickets);
    seats = new QSqlTableModel();
    ui->seats_TV->setModel(seats);
    boarding_passes = new QSqlTableModel();
    ui->boarding_pass_TV->setModel(boarding_passes);

    ui->aircrafts_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->airports_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->flights_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->seats_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tickets_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->boarding_pass_TV->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

AdminWindow::~AdminWindow() {
    qDebug() << "deleting admin window";
    delete ui;
}

void AdminWindow::on_tabWidget_currentChanged(int index) {
    switch (index) {
    case 0 :
        updateTableModel("airports", airports);
    case 1 :
        updateTableModel("aircrafts", aircrafts);
    case 2 :
        updateTableModel("boarding_passes", boarding_passes);
    case 3 :
        updateTableModel("flights", flights);
    case 4 :
        updateTableModel("seats", seats);
    case 5 :
        updateTableModel("tickets", tickets);
    }
}

void AdminWindow::updateTableModel(QString tableName, QSqlTableModel *model) {
    model->setTable(tableName);
    model->select();
    if (tableName == "airports") {
        airports->setHeaderData(0, Qt::Horizontal, QObject::tr("Код аэропорта"));
        airports->setHeaderData(1, Qt::Horizontal, QObject::tr("Название аэропорта"));
        airports->setHeaderData(2, Qt::Horizontal, QObject::tr("Город"));
        airports->setHeaderData(3, Qt::Horizontal, QObject::tr("Временная зона"));
        airports->setHeaderData(4, Qt::Horizontal, QObject::tr("Страна"));
    } else if (tableName == "aircrafts"){
        aircrafts->setHeaderData(0, Qt::Horizontal, QObject::tr("Код самолета"));
        aircrafts->setHeaderData(1, Qt::Horizontal, QObject::tr("Модель самолета"));
    } else if (tableName == "flights"){
        flights->setHeaderData(0, Qt::Horizontal, QObject::tr("Идентификатор рейса"));
        flights->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер рейса"));
        flights->setHeaderData(2, Qt::Horizontal, QObject::tr("Время вылета"));
        flights->setHeaderData(3, Qt::Horizontal, QObject::tr("Время прилета"));
        flights->setHeaderData(4, Qt::Horizontal, QObject::tr("Статус"));
        flights->setHeaderData(5, Qt::Horizontal, QObject::tr("Аэропорт прилета"));
        flights->setHeaderData(6, Qt::Horizontal, QObject::tr("Аэропорт вылета"));
        flights->setHeaderData(7, Qt::Horizontal, QObject::tr("Код самолета"));
    } else if (tableName == "tickets"){
        tickets->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер билета"));
        tickets->setHeaderData(1, Qt::Horizontal, QObject::tr("Серия паспорта"));
        tickets->setHeaderData(2, Qt::Horizontal, QObject::tr("Имя пассажира"));
        tickets->setHeaderData(3, Qt::Horizontal, QObject::tr("Цена"));
        tickets->setHeaderData(4, Qt::Horizontal, QObject::tr("Фамилия пассажира"));
        tickets->setHeaderData(5, Qt::Horizontal, QObject::tr("Номер паспорта"));
        tickets->setHeaderData(6, Qt::Horizontal, QObject::tr("Номер полета"));
        tickets->setHeaderData(7, Qt::Horizontal, QObject::tr("Класс обслуживания"));
        tickets->setHeaderData(8, Qt::Horizontal, QObject::tr("Пользователь"));
    } else if (tableName == "seats"){
        seats->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер места"));
        seats->setHeaderData(1, Qt::Horizontal, QObject::tr("Класс осблуживания"));
        seats->setHeaderData(2, Qt::Horizontal, QObject::tr("Код самолета"));
    } else if (tableName == "boarding_passes"){
        boarding_passes->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер талона"));
        boarding_passes->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер места"));
        boarding_passes->setHeaderData(2, Qt::Horizontal, QObject::tr("Идентификатор рейса"));
        boarding_passes->setHeaderData(3, Qt::Horizontal, QObject::tr("Номер билета"));
    }
}

void AdminWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Delete) {
        switch (ui->tabWidget->currentIndex()){
        case 0:{
            if (ui->airports_TV->currentIndex().row() > -1){
                airports->removeRow(ui->airports_TV->currentIndex().row());
                updateTableModel("airports", airports);
            }
        }
        case 1:{
            if (ui->aircrafts_TV->currentIndex().row() > -1){
                aircrafts->removeRow(ui->aircrafts_TV->currentIndex().row());
                updateTableModel("aircrafts", aircrafts);
            }
        }
        case 2:{
            if (ui->boarding_pass_TV->currentIndex().row() > -1){
                boarding_passes->removeRow(ui->boarding_pass_TV->currentIndex().row());
                updateTableModel("boarding_passes", boarding_passes);
            }
        }
        case 3:{
            if (ui->flights_TV->currentIndex().row() > -1){
                flights->removeRow(ui->flights_TV->currentIndex().row());
                updateTableModel("flights", flights);
            }
        }
        case 4:{
            if (ui->seats_TV->currentIndex().row() > -1){
                seats->removeRow(ui->seats_TV->currentIndex().row());
                updateTableModel("seats", seats);
            }
        }
        case 5:{
            if (ui->tickets_TV->currentIndex().row() > -1){
                tickets->removeRow(ui->tickets_TV->currentIndex().row());
                updateTableModel("tickets", tickets);
            }
        }
        }
    }
}

void AdminWindow::on_pushButton_clicked() {
    switch (ui->tabWidget->currentIndex()){
    case 0:{
        airports->insertRow(airports->rowCount());
    }
    case 1:{
        aircrafts->insertRow(aircrafts->rowCount());
    }
    case 2:{
        boarding_passes->insertRow(boarding_passes->rowCount());
    }
    case 3:{
        flights->insertRow(flights->rowCount());
    }
    case 4:{
        seats->insertRow(seats->rowCount());
    }
    case 5:{
        tickets->insertRow(tickets->rowCount());
    }
    }
}
