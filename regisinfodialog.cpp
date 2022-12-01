#include "regisinfodialog.h"
#include "ui_regisinfodialog.h"
#include"mainwindow.h"
RegisinfoDialog::RegisinfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisinfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加登记信息");
    setWindowIcon(QIcon(":/image/course.png"));
    setFixedSize(260,460);
    ui->credit_comboBox->addItems(QStringList()<<"是"<<"否");
}
bool RegisinfoDialog::ifempty()
{
    if(ui->num_lineEdit->text()!=""&&ui->name_lineEdit->text()!="")
        return true;
    else
        return false;
}
void RegisinfoDialog::Settnum(QString tempnum)
{
    tnum=tempnum;
}
void RegisinfoDialog::Setnum(int tempnum)
{
    ui->num_lineEdit->setText(QString::number(tempnum));
}
void RegisinfoDialog::Setname(QString tempname)
{
    ui->name_lineEdit->setText(tempname);
}
void RegisinfoDialog::SetBorrowDate(QDate date){
    ui->time_lineEdit->setText(date.toString());
}
//void RegisinfoDialog::Setroom(QString temproom)
//{
//    ui->jiao_comboBox->setCurrentText(temproom);
//    ui->shi_comboBox->setCurrentText(temproom);
//}
void RegisinfoDialog::SetBorrow(QString yes_or_not){
    ui->credit_comboBox->setCurrentText(yes_or_not);
}
void RegisinfoDialog::SetCardNum(QString card){
    ui->card_lineEdit->setText(card);
}
int RegisinfoDialog::Num()
{
    return ui->num_lineEdit->text().toInt();
}
QString RegisinfoDialog::Name()
{
    return ui->name_lineEdit->text();
}

QString RegisinfoDialog::Borrow(){
    return ui->credit_comboBox->currentText();
}
QDate RegisinfoDialog::BorrowDate(){
    QString date = ui->time_lineEdit->text();
    QDate temp = QDate::fromString(date,"yyyy/MM/dd");
    return temp;
}
QString RegisinfoDialog::cardNum(){
    return ui->card_lineEdit->text();
}
RegisinfoDialog::~RegisinfoDialog()
{
    delete ui;
}
