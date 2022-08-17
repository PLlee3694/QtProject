#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    setWindowTitle("搜索教师信息");
    setWindowIcon(QIcon(":/image/find.png"));
    setFixedSize(270,150);
    ui->title_label->setAlignment(Qt::AlignHCenter);
}

QString FindDialog::Num()
{
    return ui->num_lineEdit->text();
}

FindDialog::~FindDialog()
{
    delete ui;
}
