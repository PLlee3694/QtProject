#include "informationdialog.h"
#include "ui_informationdialog.h"
#include"mainwindow.h"
InformationDialog::InformationDialog(QWidget *parent,QString num) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    resize(300,360);
    QString title=MainWindow::books.num_for_books[num].name;
    title.append("的信息");
    setWindowTitle(title);
    setWindowIcon(QIcon(":/image/teacher-Regisinfo.png"));
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->baseinfo_pushButton,&QPushButton::clicked,[=]{ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->regisinfo_pushButton,&QPushButton::clicked,[=]{ui->stackedWidget->setCurrentIndex(1);});
    ui->tableWidget->setRowCount(8);
    ui->tableWidget->setVerticalHeaderLabels(QStringList()<<"编号"<<"书名"<<"作者"<<"出版日期"<<"出版社"<<"类型"<<"库存"<<"页数");
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(num));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::books.num_for_books[num].name));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::books.num_for_books[num].author));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(QString(MainWindow::books.num_for_books[num].comeOutDate.toString("yyyy/MM/dd"))));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::books.num_for_books[num].press));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::books.num_for_books[num].type));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(QString::number(MainWindow::books.num_for_books[num].storage)));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(QString::number(MainWindow::books.num_for_books[num].page)));
    ui->tableWidget_2->setRowCount(5);
    ui->tableWidget_2->setVerticalHeaderLabels(QStringList()<<"登记号"<<"书册名称"<<"是否借出"<<"借出时间"<<"借书证号");
    int cnum=MainWindow::books.num_for_books[num].storage;
    ui->tableWidget_2->setColumnCount(cnum);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<cnum;i++)
    {
        int row=0;
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(QString::number(MainWindow::books.num_for_books[num].Regisinfos[i].Regisinfo_num)));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[num].Regisinfos[i].Regisinfo_name));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[num].Regisinfos[i].borrow_or_not));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[num].Regisinfos[i].borrow_time.toString("yyyy/MM/dd")));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[num].Regisinfos[i].card_number));
    }
}

InformationDialog::~InformationDialog()
{
    delete ui;
}
