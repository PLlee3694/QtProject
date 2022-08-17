#include "screeningenderdialog.h"
#include "ui_screeningenderdialog.h"

ScreeningenderDialog::ScreeningenderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeningenderDialog)
{
    ui->setupUi(this);
    ui->choose_comboBox->addItems(QStringList()<<"男"<<"女");
    ui->title_label->setAlignment(Qt::AlignHCenter);
    setWindowIcon(QIcon(":/image/gender.png"));
    setFixedSize(240,150);
}

int ScreeningenderDialog::Choose()
{
    return ui->choose_comboBox->currentIndex();
}


ScreeningenderDialog::~ScreeningenderDialog()
{
    delete ui;
}
