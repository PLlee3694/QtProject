#include "borrobynamedialog.h"

borrowbynameDialog::borrobynameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowbynameDialog)
{
    ui->setupUi(this);
    setFixedSize(240,150);
}

QString borrowbynameDialog::Choose()
{
    return ui->bookname_lineEdit->text();
}


ScreeningenderDialog::~ScreeningenderDialog()
{
    delete ui;
}
