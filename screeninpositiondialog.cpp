#include "screeninpositiondialog.h"
#include "ui_screeninpositiondialog.h"

ScreeninpositionDialog::ScreeninpositionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeninpositionDialog)
{
    ui->setupUi(this);
    ui->choose_comboBox->addItems(QStringList()<<"教授"<<"副教授"<<"讲师"<<"助教");
    ui->title_label->setAlignment(Qt::AlignHCenter);
    setWindowIcon(QIcon(":/image/position.png"));
    setFixedSize(240,150);
}

int ScreeninpositionDialog::Choose()
{
    return ui->choose_comboBox->currentIndex();
}

ScreeninpositionDialog::~ScreeninpositionDialog()
{
    delete ui;
}
