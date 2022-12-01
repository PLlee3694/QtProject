#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include"logindialog.h"
#include<QFileDialog>
#include<QPushButton>
#include"inputdialog.h"
#include"changedialog.h"
#include"deletedialog.h"
#include<QMessageBox>
#include<algorithm>
#include"regisinfosdialog.h"
#include"finddialog.h"
#include"informationdialog.h"
#include<QLabel>
using namespace std;
BookInformationTable UserMainWindow::books;
QString UserMainWindow::user_num="";
UserMainWindow::UserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    //设置主窗口属性
    ui->setupUi(this);
    setFixedSize(955,700);
    setWindowTitle("图书室信息管理系统");
    setWindowIcon(QIcon(":/image/book.png"));



    //创建汇总表格
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"书名"<<"作者"<<"出版日期"<<"出版社"<<"类型"<<"库存册数"<<"页数"<<"登记信息");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    //创建筛选副表
//    ui->tableWidget_2->setColumnCount(9);
//    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"编号"<<"书名"<<"作者"<<"出版日期"<<"出版社"<<"类型"<<"库存册数"<<"页数"<<"登记信息");
//    ui->tableWidget_2->setRowCount(0);
//    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //实现打开按钮功能
    ui->actionopen->setIcon(QIcon(":/image/open.png"));
    connect(ui->actionopen,&QAction::triggered,
            [=](){
        QString file1=QFileDialog::getOpenFileName(this,"打开书籍信息文件",QDir::currentPath(),"文本文件(*.txt)");
        if(file1.isEmpty())
            return;
        //创建成功，打开文件
        UserMainWindow::books.Readbookfromfile(file1);
        Update();
        ui->tableWidget->show();
    });

    //实现查询书籍信息功能
    ui->actionfind->setIcon(QIcon(":/image/find.png"));
    connect(ui->actionfind,&QAction::triggered,
            [=]{
        FindDialog * find=new FindDialog;
        int ret=find->exec();
        if(ret==QDialog::Accepted)
        {
            if(UserMainWindow::books.num_for_books.find(find->Num())!=UserMainWindow::books.num_for_books.end())
            {
                InformationDialog * info=new InformationDialog (this,find->Num());
                info->exec();
            }
            else
            {
                QMessageBox::warning(this,"警告","该编号信息不存在");
            }
        }
    });
    //实现查询个人信息按钮
     ui->actionSearchPersonal->setIcon(QIcon(":/image/mine.png"));

}
void UserMainWindow::Update()
{
    Labeltnum->setText(QString::number(UserMainWindow::books.tnum));
    ui->tableWidget->setRowCount(UserMainWindow::books.tnum);

    int row=0;
    for(auto it=UserMainWindow::books.num_for_books.begin();it!=UserMainWindow::books.num_for_books.end();it++)
    {
        int col=0;

        QPushButton * butn=new QPushButton("查看登记信息");
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.num));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.author));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.comeOutDate.toString("yyyy/MM/dd")));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.press));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it->second.type));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(it->second.storage)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(it->second.page)));
        ui->tableWidget->setCellWidget(row,col++,butn);
        row++;
        connect(butn,&QPushButton::clicked,this,&UserMainWindow::Showregis);
    }
}

void UserMainWindow::Showregis()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    RegisinfosDialog * regiswidget;

    index = this->ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    regiswidget=new RegisinfosDialog (this,this->ui->tableWidget->item(row,0)->text());

    regiswidget->show();
}
UserMainWindow::~UserMainWindow()
{
    delete ui;
}
