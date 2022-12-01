#include "regisinfosdialog.h"
#include "ui_regisinfosdialog.h"
#include"mainwindow.h"
RegisinfosDialog::RegisinfosDialog(QWidget *parent,QString tnum) :
    QDialog(parent),
    ui(new Ui::RegisinfosDialog)
{
    ui->setupUi(this);
    QString title=MainWindow::books.num_for_books[tnum].name;
    title.append("的登记信息");
    setWindowTitle(title);
    setWindowIcon(QIcon(":/image/course.png"));
    setFixedSize(742,300);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"登记号"<<"书籍名称"<<"是否借出"<<"借出时间"<<"借书证号");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int cnum=MainWindow::books.num_for_books[tnum].storage;
    ui->tableWidget->setRowCount(cnum);
    for(int i=0;i<cnum;i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(QString::number(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_num)));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_name));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[tnum].Regisinfos[i].borrow_or_not));
        QString temproom=MainWindow::books.num_for_books[tnum].Regisinfos[i].borrow_time.toString("yyyy/MM/dd");

        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(temproom));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[tnum].Regisinfos[i].card_number));
}
}

RegisinfosDialog::~RegisinfosDialog()
{
    delete ui;
}
