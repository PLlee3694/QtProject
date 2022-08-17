#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMainWindow>
#include<QMessageBox>
#include"mainwindow.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setFixedSize(300,180);
    setWindowTitle("教师管理系统-登录界面");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    ui->Count_lineEdit->setFocus();
    ui->Count_lineEdit->setPlaceholderText("username");
    ui->Password_lineEdit->setPlaceholderText("password");
    connect(ui->Close_pushButton,&QPushButton::clicked,this,&QMainWindow::close);
    connect(ui->Login_pushButton,&QPushButton::clicked,this,&LoginDialog::Login_Success);
}

void LoginDialog::Login_Success()
{
    if(ui->Count_lineEdit->text()==""||ui->Password_lineEdit->text()=="")
    {
        QMessageBox::warning(this,"警告","用户名或密码不能为空！");
        this->show();
    }
    else if((ui->Count_lineEdit->text()=="71120203"&&ui->Password_lineEdit->text()!="71120203")||
            (ui->Count_lineEdit->text()!="71120203"&&ui->Password_lineEdit->text()=="71120203")||
             (ui->Count_lineEdit->text()!="71120203"&&ui->Password_lineEdit->text()!="71120203"))
    {
        QMessageBox::warning(this,"警告","你输入的账号或密码不正确，请重新输入！");
        ui->Password_lineEdit->clear();
        this->show();
    }
    else if(ui->Count_lineEdit->text()=="71120203"&&ui->Password_lineEdit->text()=="71120203")
    {
        MainWindow::user_num=ui->Count_lineEdit->text();
        ui->Password_lineEdit->clear();
        this->close();
        emit Showmainwindow();
    }
}




LoginDialog::~LoginDialog()
{
    delete ui;
}
