#include "mainwindow.h"
#include "ui_mainwindow.h"
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
BookInformationTable MainWindow::books;
QString MainWindow::user_num="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //设置主窗口属性
    ui->setupUi(this);
    setFixedSize(955,700);
    setWindowTitle("图书室信息管理系统");
    setWindowIcon(QIcon(":/image/book.png"));
    ui->stackedWidget->setCurrentIndex(0);

    //创建状态栏
    Labeltnum=new QLabel(QString::number(MainWindow::books.tnum),this);
    QStatusBar * statusbur=statusBar();
    setStatusBar(statusbur);
    statusbur->setSizeGripEnabled(false);
    statusbur->addWidget(new QLabel("当前书目总数: ",this));
    statusbur->addWidget(Labeltnum);

    //创建总表格
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"书名"<<"作者"<<"出版日期"<<"出版社"<<"类型"<<"库存册数"<<"页数"<<"登记信息");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //实现新建按钮功能
    ui->actionnew->setIcon(QIcon(":/image/new.png"));
    connect(ui->actionnew,&QAction::triggered,ui->tableWidget,&QWidget::show);

    //实现关闭按钮功能
    ui->actionclose->setIcon(QIcon(":/image/close.png"));
    connect(ui->actionclose,&QAction::triggered,this,&MainWindow::Closethewidget);

    //实现打开按钮功能
    ui->actionopen->setIcon(QIcon(":/image/open.png"));
    connect(ui->actionopen,&QAction::triggered,
            [=](){
        QString file1=QFileDialog::getOpenFileName(this,"打开书籍信息文件",QDir::currentPath(),"文本文件(*.txt)");
        if(file1.isEmpty())
            return;
        //创建成功，打开文件
        MainWindow::books.Readbookfromfile(file1);
        Update();
        ui->tableWidget->show();
    });

    //实现保存按钮功能
    ui->actionsave->setIcon(QIcon(":/image/save.png"));
    connect(ui->actionsave,&QAction::triggered,
            [=](){
        QString file2=QFileDialog::getSaveFileName(this,"保存书籍信息文件",QDir::currentPath(),"文本文件(*.txt)");
        if(file2.isEmpty())
            return;
        MainWindow::books.Savebooktofile(file2);
    });

    //实现添加书籍信息按钮功能
    ui->actionadd->setIcon(QIcon(":/image/add.png"));
    connect(ui->actionadd,&QAction::triggered,
            [=](){
        InputDialog *input=new InputDialog(this);
        int ret=input->exec();
        if(ret==QDialog::Accepted)
        {
            ui->tableWidget->show();
            Update();
            QMessageBox::about(this,"Success","添加成功!");
        }
    });

    //实现借还书籍按钮功能
    ui->actionchange->setIcon(QIcon(":/image/change.png"));
    connect(ui->actionchange,&QAction::triggered,
            [&](){
        DeleteDialog *change1=new DeleteDialog(this,"输入书名以借还书籍");
        change1->setWindowTitle("借还书籍");
        int ret1=change1->exec();
        QString change_num;
        if(ret1==QDialog::Accepted)
        {
            for(unordered_map<QString,BookInformation>::iterator it=MainWindow::books.num_for_books.begin();it!=MainWindow::books.num_for_books.end();++it){
                if(change1->Name()==it->second.name)
                    change_num =it->first;
            }
            if(MainWindow::books.num_for_books.find(change_num)!=MainWindow::books.num_for_books.end())
            {
                ChangeDialog *change2=new ChangeDialog(this,change_num);
                int ret2=change2->exec();
                if(ret2==QDialog::Accepted)
                {
                    Update();
                    QMessageBox::about(this,"Success","修改成功!");
                }
            }
            else
            {
                QMessageBox::warning(this,"警告","该书籍信息不存在");
            }
        }
    });

    //实现删除书籍信息按钮功能
    ui->actiondelet->setIcon(QIcon(":/image/delete.png"));
    connect(ui->actiondelet,&QAction::triggered,
            [&](){
        DeleteDialog *del=new DeleteDialog(this);
        int ret=del->exec();
        if(ret==QDialog::Accepted)
        {
            if(MainWindow::books.num_for_books.find(del->Num())!=MainWindow::books.num_for_books.end())
            {
                MainWindow::books.num_for_books.erase(del->Num());
                MainWindow::books.tnum--;
                ui->tableWidget->clearContents();
                Update();
                QMessageBox::about(this,"Success","删除成功!");
            }
            else
            {
                QMessageBox::warning(this,"警告","该编号信息不存在");
            }
        }
    });



    //实现查询书籍信息功能
    ui->actionfind->setIcon(QIcon(":/image/find.png"));
    connect(ui->actionfind,&QAction::triggered,
            [=]{
        FindDialog * find=new FindDialog;
        int ret=find->exec();
        if(ret==QDialog::Accepted)
        {
            if(MainWindow::books.num_for_books.find(find->Num())!=MainWindow::books.num_for_books.end())
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
    //实现直接还书功能
    connect(ui->actionreturn,&QAction::triggered,
            [&](){
        DeleteDialog *change1=new DeleteDialog(this,"输入登记号以借还书籍");
        change1->setWindowTitle("借还书籍");
        int ret1=change1->exec();
        if(ret1==QDialog::Accepted)
        {
            for(unordered_map<QString,BookInformation>::iterator it=MainWindow::books.num_for_books.begin();it!=MainWindow::books.num_for_books.end();++it){
                for(int j = 0;j<it->second.Regisinfos.size();j++){
                    if(change1->Num().toInt()==it->second.Regisinfos[j].Regisinfo_num)
                        it->second.Regisinfos[j].borrow_or_not = "否";
                        QString date_string ="1999/01/01";
                        it->second.Regisinfos[j].borrow_time=QDate::fromString(date_string,"yyyy/MM/dd");
                        it->second.Regisinfos[j].card_number="无";
                        QMessageBox::about(this,"Success","还书成功!");
                }
            }
        }
    });
}

void MainWindow::Update()
{
    Labeltnum->setText(QString::number(MainWindow::books.tnum));
    ui->tableWidget->setRowCount(MainWindow::books.tnum);

    int row=0;
    for(auto it=MainWindow::books.num_for_books.begin();it!=MainWindow::books.num_for_books.end();it++)
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
        connect(butn,&QPushButton::clicked,this,&MainWindow::Showregis);
    }
}

void MainWindow::Showregis()
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

void MainWindow::Closethewidget()
{
    ui->tableWidget->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->clearContents();
    ui->tableWidget_2->clearContents();
    MainWindow::books.num_for_books.clear();
    MainWindow::books.tnum=0;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);
    Labeltnum->setText(QString::number(MainWindow::books.tnum));
}

MainWindow::~MainWindow()
{
    delete ui;
}
