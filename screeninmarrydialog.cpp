#include "screeninmarrydialog.h"
#include "ui_screeninmarrydialog.h"

ScreeninmarryDialog::ScreeninmarryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeninmarryDialog)
{
    ui->setupUi(this);
    ui->choose_comboBox->addItems(QStringList()<<"已婚"<<"未婚");
    ui->title_label->setAlignment(Qt::AlignHCenter);
    setWindowIcon(QIcon(":/image/marry.png"));
    setFixedSize(240,150);
}

int ScreeninmarryDialog::Choose()
{
    return ui->choose_comboBox->currentIndex();
}

ScreeninmarryDialog::~ScreeninmarryDialog()
{
    delete ui;
}
