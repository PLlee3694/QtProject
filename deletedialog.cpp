#include "deletedialog.h"
#include "ui_deletedialog.h"
#include"mainwindow.h"
#include<QMessageBox>
#include<vector>
using namespace std;
DeleteDialog::DeleteDialog(QWidget *parent,QString title) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
    setWindowTitle("删除书籍信息");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    ui->title_label->setText(title);
    setFixedSize(270,150);
//    setAttribute(Qt::WA_DeleteOnClose);
    ui->title_label->setAlignment(Qt::AlignHCenter);
}

QString DeleteDialog::Num()
{
    return ui->num_lineEdit->text();
}

QString DeleteDialog::Name()
{
    return ui->num_lineEdit->text();
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}
