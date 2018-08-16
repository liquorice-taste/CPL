#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DB *base,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(base)
{
    ui->setupUi(this);

    QSqlQuery *q = new QSqlQuery(*db->getdb());
    QSqlQueryModel *md = new QSqlQueryModel();
    q->prepare("select distinct city from airports order by city asc;");
    q->exec();
    md->setQuery(*q);
    ui->CB_cityF->setModel(md);
    ui->CB_cityT->setModel(md);
    ui->CB_cityF_2->setModel(md);
    ui->CB_cityT_2->setModel(md);
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    QDate d;
    d = QDate::currentDate().addDays(-7);
    ui->dateEdit_2->setMinimumDate(d);
    ui->comboBox->addItem("Эконом");
    ui->comboBox->addItem("Бизнес");

    ui->CB_cityF->setCurrentText("");
    ui->CB_cityF_2->setCurrentText("");
    ui->CB_cityT->setCurrentText("");
    ui->CB_cityT_2->setCurrentText("");

    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery *q = new QSqlQuery(*db->getdb());
    current_fc =  ui->comboBox->currentText();
    QString d = QString::number(ui->dateEdit->date().year()) + "-" + QString::number(ui->dateEdit->date().month()) + "-" + QString::number(ui->dateEdit->date().day());
    q->prepare("select * from available_flights(:cityF, :cityT, :date, :fare_condition);");
    q->bindValue(0, ui->CB_cityT->currentText());
    q->bindValue(1, ui->CB_cityF->currentText());
    q->bindValue(2, d);
    q->bindValue(3, ui->comboBox->currentText());
    if (q->exec()) {
        QSqlQueryModel *md = new QSqlQueryModel();
        md->setQuery(*q);
        md->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер рейса"));
        md->setHeaderData(1, Qt::Horizontal, QObject::tr("Время вылета"));
        md->setHeaderData(2, Qt::Horizontal, QObject::tr("Время прилета"));
        md->setHeaderData(3, Qt::Horizontal, QObject::tr("Аэропорт вылета"));
        md->setHeaderData(4, Qt::Horizontal, QObject::tr("Аэропорт прибытия"));
        md->setHeaderData(5, Qt::Horizontal, QObject::tr("Самолет"));
        md->setHeaderData(6, Qt::Horizontal, QObject::tr("Цена"));

        ui->tableView_4->setModel(md);
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index == 0) {
    } else if (index == 1) {
    } else if (index == 2) {
        QSqlQuery *q = new QSqlQuery(*db->getdb());
        q->prepare("select * from select_user_tickets();");
        q->exec();
        QSqlQueryModel *md = new QSqlQueryModel();
        md->setQuery(*q);
        md->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер билета"));
        md->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер рейса"));
        md->setHeaderData(2, Qt::Horizontal, QObject::tr("Серия паспорта"));
        md->setHeaderData(3, Qt::Horizontal, QObject::tr("Номер паспорта"));
        md->setHeaderData(4, Qt::Horizontal, QObject::tr("Имя пассажира"));
        md->setHeaderData(5, Qt::Horizontal, QObject::tr("Фамилия пассажира"));
        md->setHeaderData(6, Qt::Horizontal, QObject::tr("Класс обслуживания"));
        md->setHeaderData(7, Qt::Horizontal, QObject::tr("Цена"));
        ui->tableView_2->setModel(md);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if ((ui->tableView_2->currentIndex().row()) > -1) {
        QFileDialog *dialog = new QFileDialog();
        dialog->setFileMode(QFileDialog::DirectoryOnly);

        QFile *outfile = new QFile();
        QString _OutputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
        if (_OutputFolder != ""){
            outfile->setFileName(_OutputFolder);
            outfile->open(QIODevice::Append | QIODevice::Text);

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0));
            QString tickt_num = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            QPrinter *printer = new QPrinter(QPrinter::PrinterResolution);
            printer->setOutputFormat(QPrinter::PdfFormat);
            printer->setPaperSize(QPrinter::A4);
            printer->setOutputFileName(_OutputFolder + "/ticket" + tickt_num + ".pdf");
            QTextDocument *q = new QTextDocument();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),1));
            QString flight_id = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),2));
            QString passport_series = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),3));
            QString passport_number = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4));
            QString name = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),5));
            QString surname = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),6));
            QString fare_condition = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),7));
            QString price = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            QSqlQuery *query = new QSqlQuery();
            query->prepare("select * from info_for_ticket(:tickt_num);");
            query->bindValue(0, tickt_num);
            query->exec();
            QString cityF;
            QString cityT;
            QDateTime datetimedep;
            QDateTime datetimearr;
            QTime travel_time;
            QString airportf;
            QString airportt;
            QString aircraft_model;
            while (query->next()){
                cityF = query->value(0).toString();
                cityT = query->value(1).toString();
                datetimedep = query->value(2).toDateTime();
                datetimearr = query->value(3).toDateTime();
                travel_time = query->value(4).toTime();
                airportf = query->value(5).toString();
                airportt = query->value(6).toString();
                aircraft_model = query->value(7).toString();
            }
            QString str;
            str=
                    "<table border='1' style='border-color: transparent; width: 100%;'>"
                    "<tbody>"
                    "<tr style='height: 20px;'>"
                    "<td style='width: 65.0877%; height: 20px;'>"
                    "<p style='font-size: 40px;'>Маршрутная квитанция</p>"
                    "<p>ELECTRONIC TICKET</p>"
                    "</td>"
                    "<td style='width: 34.9123%; height: 20px;'>"
                    "<p style='text-align: left;'><span><img src=':/images/logo.png' width='200' height='100' /></span></p>"
                    "<p style='text-align: left;'>НОМЕР ВАШЕГО БИЛЕТА:</p>"
                    "<p style='text-align: left;'><span style='color: #ffffff; background-color: #000000;'><strong>" + tickt_num +"</strong></span></p>"

                                                                                                                                  "</td>"
                                                                                                                                  "</tr>"
                                                                                                                                  "</tbody>"
                                                                                                                                  "</table>"
                                                                                                                                  "<p style='font-size: 20px;'>Данные о пассажире</p>"
                                                                                                                                  "<hr style ='width: 100%;' />"
                                                                                                                                  "<table border='1' style='border-collapse: collapse; width: 100%; border-color: transparent;'>"
                                                                                                                                  "<tbody>"
                                                                                                                                  "<tr>"
                                                                                                                                  "<td style='width: 50%;'>ПАССАЖИР</td>"
                                                                                                                                  "<td style='width: 50%;'>ПАСПОРТ</td>"
                                                                                                                                  "</tr>"
                                                                                                                                  "<tr>"
                                                                                                                                  "<td style='width: 50%;'>" + surname + " " + name + "</td>"
                                                                                                                                                                                      "<td style='width: 50%;'>" + passport_series + " " + passport_number + "</td>"
                                                                                                                                                                                                                                                             "</tr>"
                                                                                                                                                                                                                                                             "</tbody>"
                                                                                                                                                                                                                                                             "</table>"
                                                                                                                                                                                                                                                             "<p style='font-size: 20px;'>Информация о маршруте</p>"
                                                                                                                                                                                                                                                             "<hr style ='width: 100%;'/>"
                                                                                                                                                                                                                                                             "<table border='1' style='border-collapse: collapse; width: 100%; border-color: transparent;'>"
                                                                                                                                                                                                                                                             "<tbody>"
                                                                                                                                                                                                                                                             "<tr style='height: 20px;'>"
                                                                                                                                                                                                                                                             "<td style='width: 25%; height: 20px;'>РЕЙСЫ</td>"
                                                                                                                                                                                                                                                             "<td style='width: 25%; height: 20px;'>ВЫЛЕТ</td>"
                                                                                                                                                                                                                                                             "<td style='width: 25%; height: 20px;'>В ПУТИ</td>"
                                                                                                                                                                                                                                                             "<td style='width: 25%; height: 20px;'>ПРИБЫТИЕ</td>"
                                                                                                                                                                                                                                                             "</tr>"
                                                                                                                                                                                                                                                             "<tr style='height: 20px;'>"
                                                                                                                                                                                                                                                             "<td style='width: 25%; height: 20px;'>Рейс" + " " + flight_id + " " + fare_condition + "</td>"
                                                                                                                                                                                                                                                                                                                                                     "<td style='width: 25%; height: 20px;'>" + " " + cityF + " " +"</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                   "<td style='width: 25%; height: 20px;'></td>"
                                                                                                                                                                                                                                                                                                                                                                                                                   "<td style='width: 25%; height: 20px;'>" + " " + cityT + " " +"</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 "</tr>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 "<tr style='height: 20px;'>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 "<td style='width: 25%; height: 20px;'></td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 "<td style='width: 25%; height: 15px;'>"+ " " + datetimedep.time().toString("hh:mm") + " " + datetimedep.date().toString("d MMM yyyy") + "</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          "<td style='width: 25%; height: 20px;'>---" + QString::number(travel_time.hour()) + "ч." + QString::number(travel_time.minute()) + "мин." + "--&gt;</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      "<td style='width: 25%; height: 15px;'>" + " " + datetimearr.time().toString("hh:mm") + " " + datetimearr.date().toString("d MMM yyyy") + "</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                "</tr>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                "<tr style='height: 20px;'>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                "<td style='width: 25%; height: 20px;'>Самолет " + aircraft_model + "&nbsp;</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    "<td style='width: 25%; height: 20px;'>а/п " + airportf + "</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              "<td style='width: 25%; height: 20px;'></td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              "<td style='width: 25%; height: 20px;'>а/п " + airportt + "</td>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "</tr>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "</tbody>"
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        "</table>";
            //q.setHtml("<img src=:/images/logo.png></img>"
            //        "<h1>Авиабилет</h1>\n<tt>Ну привет.</tt>");
            q->setHtml(str);
            q->setPageSize(printer->pageRect().size());
            q->print(printer);
        }
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    if (ui->radioButton->isChecked()) {
        QSqlQuery *q = new QSqlQuery();
        QString d = QString::number(ui->dateEdit_2->date().year()) + "-" + QString::number(ui->dateEdit_2->date().month()) + "-" + QString::number(ui->dateEdit_2->date().day());
        q->prepare("select * from flight_status_by_route(:cityF, :cityT, :date)");
        q->bindValue(0, ui->CB_cityF_2->currentText());
        q->bindValue(1, ui->CB_cityT_2->currentText());
        q->bindValue(2, d);
        if (q->exec()) {
        QSqlQueryModel *m = new QSqlQueryModel();
        m->setQuery(*q);
        m->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер рейса"));
        m->setHeaderData(1, Qt::Horizontal, QObject::tr("Статус"));
        m->setHeaderData(2, Qt::Horizontal, QObject::tr("Время вылета"));
        m->setHeaderData(3, Qt::Horizontal, QObject::tr("Время прилета"));
        m->setHeaderData(4, Qt::Horizontal, QObject::tr("Аэропорт вылета"));
        m->setHeaderData(5, Qt::Horizontal, QObject::tr("Аэропорт прибытия"));
        m->setHeaderData(6, Qt::Horizontal, QObject::tr("Самолет"));
        ui->tableView_3->setModel(m);
        }
    } else if (ui->radioButton_2->isChecked()) {
        QSqlQuery *q = new QSqlQuery();
        q->prepare("select * from flight_status_by_id(:fl_id)");
        q->bindValue(0, ui->LEflightd->text());
        q->exec();
        QSqlQueryModel *md = new QSqlQueryModel();
        md->setQuery(*q);
        md->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер рейса"));
        md->setHeaderData(1, Qt::Horizontal, QObject::tr("Статус"));
        md->setHeaderData(2, Qt::Horizontal, QObject::tr("Время вылета"));
        md->setHeaderData(3, Qt::Horizontal, QObject::tr("Время прилета"));
        md->setHeaderData(4, Qt::Horizontal, QObject::tr("Аэропорт вылета"));
        md->setHeaderData(5, Qt::Horizontal, QObject::tr("Аэропорт прибытия"));
        md->setHeaderData(6, Qt::Horizontal, QObject::tr("Самолет"));
        ui->tableView_3->setModel(md);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if ((ui->tableView_2->currentIndex().row()) > -1) {
        QModelIndex ind = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(), 1);
        ui->tableView_2->setCurrentIndex(ind);
        int fl_id = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toInt();
        ind = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(), 6);
        ui->tableView_2->setCurrentIndex(ind);
        QString fare_c = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();
        ind = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(), 0);
        ui->tableView_2->setCurrentIndex(ind);
        QString ticket_no = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();
        BoardingPassWindow *w = new BoardingPassWindow(this, db, fl_id, ticket_no, fare_c);
        w->show();
        this->hide();
    }
}

void MainWindow::on_tableView_4_doubleClicked(const QModelIndex &index)
{
    QModelIndex ind = ui->tableView_4->model()->index(ui->tableView_4->currentIndex().row(), 0);
    ui->tableView_4->setCurrentIndex(ind);
    QString flight_id = ui->tableView_4->model()->data(ui->tableView_4->currentIndex()).toString();

    ind = ui->tableView_4->model()->index(ui->tableView_4->currentIndex().row(), 6);
    ui->tableView_4->setCurrentIndex(ind);
    QString price = ui->tableView_4->model()->data(ui->tableView_4->currentIndex()).toString();


    PurchaseWindow * w = new PurchaseWindow(this, db, flight_id, current_fc, price);
    w->show();
    this->hide();
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->tableView_2->currentIndex().row() > -1) {

        QFileDialog *dialog = new QFileDialog();
        dialog->setFileMode(QFileDialog::DirectoryOnly);

        QFile *outfile = new QFile();
        QString _OutputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
        if (_OutputFolder != ""){
            outfile->setFileName(_OutputFolder);
            outfile->open(QIODevice::Append | QIODevice::Text);


            ui->tableView_2->setCurrentIndex(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0));
            QString tickt_num = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();

            QSqlQuery *query = new QSqlQuery();
            query->prepare("select * from info_for_boarding_pass(:tickt_num);");
            query->bindValue(0, tickt_num);
            query->exec();
            QString cityF;
            QString cityT;
            QDateTime datetimedep;
            QDateTime datetimearr;
            QString airportf;
            QString airportt;
            QString seat_no;
            QString flight_id;
            QString name;
            QString surname;
            QTime b_before;
            QString b_no;
            while (query->next()){
                cityF = query->value(0).toString();
                cityT = query->value(1).toString();
                datetimedep = query->value(2).toDateTime();
                datetimearr = query->value(3).toDateTime();
                airportf = query->value(4).toString();
                airportt = query->value(5).toString();
                seat_no = query->value(6).toString();
                flight_id = query->value(7).toString();
                surname = query->value(8).toString();
                name = query->value(9).toString();
                b_no = query->value(10).toString();
            }
            b_before = datetimedep.time().addSecs(-1800);
            QString str;
            str= "<h1><span style='color: #993366;'>&nbsp; Посадочный талон</span></h1>"
                    "<h2><span style='color: #000000;'>&nbsp; &nbsp;"+surname + " " + name + "</span></h2>"
                    "<table style='height: 73px; width: 518px; background-color: #e0e2e5; margin-left: auto; margin-right: auto;'>"
                    "<tbody>"
                    "<tr>"
                    "<td style='width: 96px;'>&nbsp;</td>"
                    "<td style='width: 113px; text-align: right;'><span style='color: #993366;'>из</span></td>"
                    "<td style='width: 65.6667px;'><span style='color: #993366;'>&nbsp;</span></td>"
                    "<td style='width: 113.333px;'><span style='color: #993366;'>в</span></td>"
                    "<td style='width: 99px;'>&nbsp;</td>"
                    "</tr>"
                    "<tr>"
                    "<td style='width: 96px; text-align: right;'>вылет"
                    "<p style='text-align: right;'>"+datetimedep.time().toString()+"</p>"
                    "<p style='text-align: right;'>"+datetimedep.date().toString()+"</p>"
                    "</td>"
                    "<td style='width: 113px; text-align: right;'>"
                    "<h1><strong>"+airportf+"</strong></h1>"
                    "</td>"
                    "<td style='width: 65.6667px;'><img src='qrc:/images/plane.png' width='110' height='94' /></td>"
                    "<td style='width: 113.333px;'>"
                    "<h1><strong>"+airportt+"</strong></h1>"
                    "</td>"
                    "<td style='width: 99px;'>"
                    "<p>прилет</p>"
                    "<p>"+datetimearr.time().toString()+"</p>"
                    "<p>"+datetimearr.date().toString()+"</p>"
                    "</td>"
                    "</tr>"
                    "<tr>"
                    "<td style='width: 209px; text-align: right;' colspan='2'>" + airportf + "</td>"
                    "<td style='width: 65.6667px;'>&nbsp;</td>"
                    "<td style='width: 212.333px;' colspan='2'>" + airportt + "</td>"
                    "</tr>"
                    "</tbody>"
                    "</table>"
                    "<table style='width: 518px; margin-left: auto; margin-right: auto;'>"
                    "<tbody>"
                    "<tr>"
                    "<td><span style='color: #993366;'>Рейс</span></td>"
                    "<td><span style='color: #993366;'>Место</span></td>"
                    "<td><span style='color: #993366;'>Посадка до</span></td>"
                    "<td><span style='color: #993366;'>№ регистрации</span></td>"
                    "<td><span style='color: #993366;'>Выход</span></td>"
                    "</tr>"
                    "<tr>"
                    "<td><strong>" + flight_id + "</strong></td>"
                    "<td><strong>" + seat_no + "</strong></td>"
                    "<td><strong>" + b_before.toString() + "</strong></td>"
                    "<td><strong>" + b_no + "</strong></td>"
                    "<td>"
                    "<p><strong>уточните на </strong></p>"
                    "<p><strong>мониторах</strong></p>"
                    "</td>"
                    "</tr>"
                    "</tbody>"
                    "</table>";

            QPrinter *printer = new QPrinter(QPrinter::PrinterResolution);
            printer->setOutputFormat(QPrinter::PdfFormat);
            printer->setPaperSize(QPrinter::A4);
            printer->setOutputFileName(_OutputFolder + "/boarding" + b_no + ".pdf");
            QTextDocument *q = new QTextDocument();
            q->setHtml(str);
            q->setPageSize(printer->pageRect().size());
            q->print(printer);
        }
    }
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QModelIndex ind = ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(), 0);
    ui->tableView_2->setCurrentIndex(ind);
    QString ticket_no = ui->tableView_2->model()->data(ui->tableView_2->currentIndex()).toString();
    QSqlQuery *q = new QSqlQuery();
    q->prepare("select tick_has_bp(:tick_no);");
    q->bindValue(0, ticket_no);
    bool b;
    q->exec();
    while (q->next()) {
        b = q->value(0).toBool();
        if (b){
            ui->pushButton_5->setEnabled("true");
            ui->pushButton_2->setDisabled("true");
        } else {
            ui->pushButton_2->setEnabled("true");
            ui->pushButton_5->setDisabled("true");
        }
    }
}
