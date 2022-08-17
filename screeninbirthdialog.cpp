#include "screeninbirthdialog.h"
#include "ui_screeninbirthdialog.h"

ScreeninbirthDialog::ScreeninbirthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeninbirthDialog)
{
    ui->setupUi(this);
    ui->choose_comboBox->addItems(QStringList()<<"以前"<<"以后");
    ui->titlelabel->setAlignment(Qt::AlignHCenter);
    setWindowIcon(QIcon(":/image/birth.png"));
    setFixedSize(240,150);
}

QDate ScreeninbirthDialog::Time()
{
    return ui->dateEdit->date();
}

bool ScreeninbirthDialog::Choose()
{
    if(ui->choose_comboBox->currentIndex()==0)
        return true;
    else
        return false;
}
ScreeninbirthDialog::~ScreeninbirthDialog()
{
    delete ui;
}
