#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"logindialog.h"
#include<QFileDialog>
#include<QPushButton>
#include"inputdialog.h"
#include"changedialog.h"
#include"deletedialog.h"
#include<aboutdialog.h>
#include<QMessageBox>
#include<algorithm>
#include"coursesdialog.h"
#include"screeninbirthdialog.h"
#include"screeninpositiondialog.h"
#include"screeningenderdialog.h"
#include"screeningradedialog.h"
#include"screeninmarrydialog.h"
#include"finddialog.h"
#include"informationdialog.h"
#include<QLabel>
using namespace std;
TeacherInformationTable MainWindow::teachers;
QString MainWindow::user_num="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //设置主窗口属性
    ui->setupUi(this);
    setFixedSize(955,700);
    setWindowTitle("教师信息管理系统");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    ui->stackedWidget->setCurrentIndex(0);

    //创建状态栏
    Labeltnum=new QLabel(QString::number(MainWindow::teachers.tnum),this);
    QStatusBar * statusbur=statusBar();
    setStatusBar(statusbur);
    statusbur->setSizeGripEnabled(false);
    statusbur->addWidget(new QLabel("当前教师总数: ",this));
    statusbur->addWidget(Labeltnum);

    //创建汇总表格
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资（元）"<<"婚否"<<"授课信息");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //创建筛选副表
    ui->tableWidget_2->setColumnCount(9);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"编号"<<"姓名"<<"性别"<<"出生年月"<<"职称"<<"最后学历"<<"工资（元）"<<"婚否"<<"授课信息");
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

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
        QString file1=QFileDialog::getOpenFileName(this,"打开教师信息文件",QDir::currentPath(),"文本文件(*.txt)");
        if(file1.isEmpty())
            return;
        //创建成功，打开文件
        MainWindow::teachers.Readteacherfromfile(file1);
        Update();
        ui->tableWidget->show();
    });

    //实现保存按钮功能
    ui->actionsave->setIcon(QIcon(":/image/save.png"));
    connect(ui->actionsave,&QAction::triggered,
            [=](){
        QString file2=QFileDialog::getSaveFileName(this,"保存教师信息文件",QDir::currentPath(),"文本文件(*.txt)");
        if(file2.isEmpty())
            return;
        MainWindow::teachers.Saveteachertofile(file2);
    });

    //实现添加教师信息按钮功能
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

    //实现修改教师信息按钮功能
    ui->actionchange->setIcon(QIcon(":/image/change.png"));
    connect(ui->actionchange,&QAction::triggered,
            [&](){
        DeleteDialog *change1=new DeleteDialog(this,"输入教师编号以修改教师信息");
        change1->setWindowTitle("修改教师信息");
        int ret1=change1->exec();
        if(ret1==QDialog::Accepted)
        {
            if(MainWindow::teachers.num_for_teachers.find(change1->Num())!=MainWindow::teachers.num_for_teachers.end())
            {
                ChangeDialog *change2=new ChangeDialog(this,change1->Num());
                int ret2=change2->exec();
                if(ret2==QDialog::Accepted)
                {
                    Update();
                    QMessageBox::about(this,"Success","修改成功!");
                }
            }
            else
            {
                QMessageBox::warning(this,"警告","该编号信息不存在");
            }
        }
    });

    //实现删除教师信息按钮功能
    ui->actiondelet->setIcon(QIcon(":/image/delete.png"));
    connect(ui->actiondelet,&QAction::triggered,
            [&](){
        DeleteDialog *del=new DeleteDialog(this);
        int ret=del->exec();
        if(ret==QDialog::Accepted)
        {
            if(MainWindow::teachers.num_for_teachers.find(del->Num())!=MainWindow::teachers.num_for_teachers.end())
            {
                MainWindow::teachers.num_for_teachers.remove(del->Num());
                MainWindow::teachers.tnum--;
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

    //实现登出当前账户按钮功能
    ui->actionlogout->setIcon(QIcon(":/image/logout.png"));
    connect(ui->actionlogout,&QAction::triggered,
            [=](){this->close();emit return_to_the_login();});

    //实现展示当前账户信息按钮功能
    ui->actionabout->setIcon(QIcon(":/image/mine.png"));
    connect(ui->actionabout,&QAction::triggered,
            [=](){AboutDialog *about=new AboutDialog(this);about->exec();});

    //实现按出生日期筛选按钮功能
    ui->actionsortinbirth->setIcon(QIcon(":/image/birth.png"));
    connect(ui->actionsortinbirth,&QAction::triggered,
            [=]{
        ScreeninbirthDialog * screen=new ScreeninbirthDialog;
        screen->setWindowTitle("筛选");
        int ret=screen->exec();
        if(ret==QDialog::Accepted)
        {
            Screeninbirth(screen->Time(),screen->Choose());
        }
    });

    //实现按职称筛选按钮功能
    ui->actionscreeninposition->setIcon(QIcon(":/image/position.png"));
    connect(ui->actionscreeninposition,&QAction::triggered,
            [=]{
        ScreeninpositionDialog * screen=new ScreeninpositionDialog;
        screen->setWindowTitle("筛选");
        int ret=screen->exec();
        if(ret==QDialog::Accepted)
        {
            Screeninposition(screen->Choose());
        }
    });

    //实现按学历筛选按钮功能
    ui->actionscreeningrade->setIcon(QIcon(":/image/grade.png"));
    connect(ui->actionscreeningrade,&QAction::triggered,
            [=]{
        ScreeningradeDialog * screen=new ScreeningradeDialog;
        screen->setWindowTitle("筛选");
        int ret=screen->exec();
        if(ret==QDialog::Accepted)
        {
            Screeningrade(screen->Choose());
        }
    });

    //实现按性别筛选按钮功能
    ui->actionscreeningender->setIcon(QIcon(":/image/gender.png"));
    connect(ui->actionscreeningender,&QAction::triggered,
            [=]{
        ScreeningenderDialog * screen=new ScreeningenderDialog;
        screen->setWindowTitle("筛选");
        int ret=screen->exec();
        if(ret==QDialog::Accepted)
        {
            Screeningender(screen->Choose());
        }
    });

    //实现按婚否筛选按钮功能
    ui->actionscreeninmarry->setIcon(QIcon(":/image/marry.png"));
    connect(ui->actionscreeninmarry,&QAction::triggered,
            [=]{
        ScreeninmarryDialog * screen=new ScreeninmarryDialog;
        screen->setWindowTitle("筛选");
        int ret=screen->exec();
        if(ret==QDialog::Accepted)
        {
            Screeninmarry(screen->Choose());
        }
    });

    //实现查询教师信息功能
    ui->actionfind->setIcon(QIcon(":/image/find.png"));
    connect(ui->actionfind,&QAction::triggered,
            [=]{
        FindDialog * find=new FindDialog;
        int ret=find->exec();
        if(ret==QDialog::Accepted)
        {
            if(MainWindow::teachers.num_for_teachers.find(find->Num())!=MainWindow::teachers.num_for_teachers.end())
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

    //实现返回总表按钮功能
    ui->actionreturntotheindex0->setIcon(QIcon(":/image/return.png"));
    connect(ui->actionreturntotheindex0,&QAction::triggered,[=]{ui->stackedWidget->setCurrentIndex(0);Labeltnum->setText(QString::number(MainWindow::teachers.tnum));});
}

void MainWindow::Update()
{
    Labeltnum->setText(QString::number(MainWindow::teachers.tnum));
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setRowCount(MainWindow::teachers.tnum);

    int row=0;
    for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
    {
        int col=0;
        QString gender;
        if(it  .value().gender)
            gender="男";
        else
            gender="女";
        QString marry;
        if(it  .value().marry)
            marry="已婚";
        else
            marry="未婚";
        QPushButton * butn=new QPushButton("查看授课信息");
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().num));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(gender));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().position));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().grade));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(it  .value().salary));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(marry));
        ui->tableWidget->setCellWidget(row,col++,butn);
        row++;
        connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
    }
}

void MainWindow::Showcourse()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    CoursesDialog * courseswidget;
    if(ui->stackedWidget->currentIndex()==0)
    {
        index = this->ui->tableWidget->indexAt(QPoint(x, y));
        int row = index.row();
        courseswidget=new CoursesDialog (this,this->ui->tableWidget->item(row,0)->text());
    }
    else
    {
        index = this->ui->tableWidget_2->indexAt(QPoint(x, y));
        int row = index.row();
        courseswidget=new CoursesDialog (this,this->ui->tableWidget_2->item(row,0)->text());
    }
    courseswidget->show();
}

void MainWindow::Closethewidget()
{
    ui->tableWidget->hide();
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->clearContents();
    ui->tableWidget_2->clearContents();
    MainWindow::teachers.num_for_teachers.clear();
    MainWindow::teachers.tnum=0;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);
    Labeltnum->setText(QString::number(MainWindow::teachers.tnum));
}

void MainWindow::Screeninbirth(QDate time,bool choose)
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    int rowIndex =0;
    if(choose==true)
    {
        for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
        {
            if(it  .value().birth<=time)
            {
                ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
                int col=0;
                QString gender;
                if(it  .value().gender)
                    gender="男";
                else
                    gender="女";
                QString marry;
                if(it  .value().marry)
                    marry="已婚";
                else
                    marry="未婚";
                QPushButton * butn=new QPushButton("查看授课信息");
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
                ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
                connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
            }
        }
        Labeltnum->setText(QString::number(rowIndex));
    }
    else
    {
        for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
        {
            if(it  .value().birth>=time)
            {
                ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
                int col=0;
                QString gender;
                if(it  .value().gender)
                    gender="男";
                else
                    gender="女";
                QString marry;
                if(it  .value().marry)
                    marry="已婚";
                else
                    marry="未婚";
                QPushButton * butn=new QPushButton("查看授课信息");
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
                ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
                ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
                connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
            }
        }
        Labeltnum->setText(QString::number(rowIndex));
    }
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::Screeninposition(int choose)
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    QString tempposition="";
    switch (choose)
    {
    case 0:
    {tempposition="教授";break;}
    case 1:
    {tempposition="副教授";break;}
    case 2:
    {tempposition="讲师";break;}
    case 3:
    {tempposition="助教";break;}
    default:break;
    }
    int rowIndex =0;
    for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
    {
        if(it  .value().position==tempposition)
                {
                    ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
                    int col=0;
                    QString gender;
                    if(it  .value().gender)
                        gender="男";
                    else
                        gender="女";
                    QString marry;
                    if(it  .value().marry)
                        marry="已婚";
                    else
                        marry="未婚";
                    QPushButton * butn=new QPushButton("查看授课信息");
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
                    ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
                    ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
                    connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
                }
    }
    Labeltnum->setText(QString::number(rowIndex));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::Screeningrade(int choose)
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    QString tempgrade="";
    switch (choose)
    {
    case 0:
    {tempgrade="博士";break;}
    case 1:
    {tempgrade="硕士";break;}
    case 2:
    {tempgrade="学士";break;}
    default:break;
    }
    int rowIndex =0;
    for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
    {
        if(it  .value().grade==tempgrade)
        {
            ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
            int col=0;
            QString gender;
            if(it  .value().gender)
                gender="男";
            else
                gender="女";
            QString marry;
            if(it  .value().marry)
                marry="已婚";
            else
                marry="未婚";
            QPushButton * butn=new QPushButton("查看授课信息");
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
            ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
            connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
        }
    }
    Labeltnum->setText(QString::number(rowIndex));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::Screeningender(int choose)
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    int rowIndex =0;
    for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
    {
        if(it  .value().gender!=choose)
        {
            ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
            int col=0;
            QString gender;
            if(it  .value().gender)
                gender="男";
            else
                gender="女";
            QString marry;
            if(it  .value().marry)
                marry="已婚";
            else
                marry="未婚";
            QPushButton * butn=new QPushButton("查看授课信息");
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
            ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
            connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
        }
    }
    Labeltnum->setText(QString::number(rowIndex));
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::Screeninmarry(int choose)
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);
    int rowIndex =0;
    for(auto it=MainWindow::teachers.num_for_teachers.begin();it!=MainWindow::teachers.num_for_teachers.end();it++)
    {
        if(it  .value().marry!=choose)
        {
            ui->tableWidget_2->setRowCount(++rowIndex);//总行数增加1
            int col=0;
            QString gender;
            if(it  .value().gender)
                gender="男";
            else
                gender="女";
            QString marry;
            if(it  .value().marry)
                marry="已婚";
            else
                marry="未婚";
            QPushButton * butn=new QPushButton("查看授课信息");
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().num));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().name));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(gender));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().birth.toString("yyyy/MM/dd")));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().position));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().grade));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(it  .value().salary));
            ui->tableWidget_2->setItem(rowIndex-1,col++,new QTableWidgetItem(marry));
            ui->tableWidget_2->setCellWidget(rowIndex-1,col++,butn);
            connect(butn,&QPushButton::clicked,this,&MainWindow::Showcourse);
        }
    }
    Labeltnum->setText(QString::number(rowIndex));
    ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
