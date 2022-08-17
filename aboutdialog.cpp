#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include"mainwindow.h"
#include<QString>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle("当前账户信息");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    setFixedSize(250,255);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->Ok_pushButton,&QPushButton::clicked,this,&QDialog::close);
    if(MainWindow::teachers.num_for_teachers.find(MainWindow::user_num)!=MainWindow::teachers.num_for_teachers.end())
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_1->setAlignment(Qt::AlignRight);
        ui->label_2->setAlignment(Qt::AlignRight);
        ui->label_3->setAlignment(Qt::AlignRight);
        ui->label_4->setAlignment(Qt::AlignRight);
        ui->count_label->setAlignment(Qt::AlignLeft);
        ui->count_label->setText(MainWindow::user_num);
        ui->name_label->setAlignment(Qt::AlignLeft);
        ui->name_label->setText(MainWindow::teachers.num_for_teachers[MainWindow::user_num].name);
        ui->position_label->setAlignment(Qt::AlignLeft);
        ui->position_label->setText(MainWindow::teachers.num_for_teachers[MainWindow::user_num].position);
        ui->birth_label->setAlignment(Qt::AlignLeft);
        ui->birth_label->setText(QString(MainWindow::teachers.num_for_teachers[MainWindow::user_num].birth.toString("yyyy/MM/dd")));
    }
    else
        ui->stackedWidget->setCurrentIndex(1);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
