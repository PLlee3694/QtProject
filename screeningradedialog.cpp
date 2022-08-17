#include "screeningradedialog.h"
#include "ui_screeningradedialog.h"

ScreeningradeDialog::ScreeningradeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScreeningradeDialog)
{
    ui->setupUi(this);
    ui->choose_comboBox->addItems(QStringList()<<"博士"<<"硕士"<<"学士");
    ui->title_label->setAlignment(Qt::AlignHCenter);
    setWindowIcon(QIcon(":/image/grade.png"));
    setFixedSize(240,150);
}

int ScreeningradeDialog::Choose()
{
    return ui->choose_comboBox->currentIndex();
}

ScreeningradeDialog::~ScreeningradeDialog()
{
    delete ui;
}
