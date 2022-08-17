#include "coursedialog.h"
#include "ui_coursedialog.h"
#include"mainwindow.h"
CourseDialog::CourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加授课信息");
    setWindowIcon(QIcon(":/image/course.png"));
    setFixedSize(260,460);
    ui->jiao_comboBox->addItems(QStringList()<<"教一"<<"教二"<<"教三"<<"教四"<<"教五"<<"教六"<<"教七"<<"教八");
    ui->shi_comboBox->addItems(QStringList()<<"101"<<"102"<<"103"<<"201"<<"202"<<"203"<<"301"<<"302"<<"303"<<"401"<<"402"<<"403");
    ui->class_comboBox->addItems(QStringList()<<"JS1201"<<"JS1202"<<"JS1203"<<"JS1204"<<"JS2201"<<"JS2202"<<"JS2203"<<"JS2204");
    ui->credit_comboBox->addItems(QStringList()<<"0.25"<<"0.5"<<"1"<<"2"<<"3"<<"4"<<"6");
    ui->semester_comboBox->addItems(QStringList()<<"第一学期"<<"第二学期"<<"第三学期"<<"第四学期");
}
bool CourseDialog::ifempty()
{
    if(ui->num_lineEdit->text()!=""&&ui->name_lineEdit->text()!=""&&ui->hour_lineEdit->text()!="")
        return true;
    else
        return false;
}
void CourseDialog::Settnum(QString tempnum)
{
    tnum=tempnum;
}
void CourseDialog::Setnum(int tempnum)
{
    ui->num_lineEdit->setText(QString::number(tempnum));
}
void CourseDialog::Setname(QString tempname)
{
    ui->name_lineEdit->setText(tempname);
}
void CourseDialog::Sethour(float temphour)
{
    ui->hour_lineEdit->setText(QString("%1").arg(temphour));
}
//void CourseDialog::Setroom(QString temproom)
//{
//    ui->jiao_comboBox->setCurrentText(temproom);
//    ui->shi_comboBox->setCurrentText(temproom);
//}
void CourseDialog::Setjiao(QString tempjiao)
{
    ui->jiao_comboBox->setCurrentText(tempjiao);
}
void CourseDialog::Setshi(QString tempshi)
{
    ui->shi_comboBox->setCurrentText(tempshi);
}
void CourseDialog::Setclass(QString temproom)
{
    ui->class_comboBox->setCurrentText(temproom);
}
void CourseDialog::Setcredit(float tempcredit)
{
    ui->credit_comboBox->setCurrentText(QString("%1").arg(tempcredit));
}
void CourseDialog::Setsemester(QString tempsemester)
{
    ui->semester_comboBox->setCurrentText(tempsemester);
}
int CourseDialog::Num()
{
    return ui->num_lineEdit->text().toInt();
}
QString CourseDialog::Name()
{
    return ui->name_lineEdit->text();
}
float CourseDialog::Hour()
{
    return ui->hour_lineEdit->text().toFloat();
}
//QString CourseDialog::Room()
//{
//    QString temproom="";
//    temproom=ui->jiao_comboBox->currentText();
//    temproom.append(ui->shi_comboBox->currentText());
//    return temproom;
//}
QString CourseDialog::Jiao()
{
    return ui->jiao_comboBox->currentText();
}
QString CourseDialog::Shi()
{
    return ui->shi_comboBox->currentText();
}
QString CourseDialog::Class()
{
    return ui->class_comboBox->currentText();
}
float CourseDialog::Credit()
{
    return ui->credit_comboBox->currentText().toFloat();
}
QString CourseDialog::Semester()
{
    return ui->semester_comboBox->currentText();
}

CourseDialog::~CourseDialog()
{
    delete ui;
}
