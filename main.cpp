#include "mainwindow.h"
#include <QApplication>
#include"logindialog.h"
#include<teacherinformationtable.h>
#include<QPalette>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFont myfont("楷体",12);
    a.setFont(myfont);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor(246,246,246));
    a.setPalette(palette);
    MainWindow w;
//    LoginDialog * Logindialog=new LoginDialog;
//    Logindialog->show();
//    QObject::connect(Logindialog,&LoginDialog::Showmainwindow,&w,&MainWindow::show);
//    QObject::connect(&w,&MainWindow::return_to_the_login,Logindialog,&LoginDialog::show);
//    QObject::connect(&w,&MainWindow::return_to_the_login,&w,&MainWindow::Closethewidget);
    w.show();
    return a.exec();
}
