#include "changedialog.h"
#include "ui_changedialog.h"
#include"mainwindow.h"
#include<QMessageBox>
#include"editcoursesdialog.h"
ChangeDialog::ChangeDialog(QWidget *parent,QString num) :
    QDialog(parent),gender(true),marry(true),
    ui(new Ui::ChangeDialog),change_num(num)
{
    ui->setupUi(this);
    setWindowTitle("修改教师信息");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    setFixedSize(260,443);
    //    setAttribute(Qt::WA_DeleteOnClose);
    ui->grade_comboBox->addItems(QStringList()<<"博士"<<"硕士"<<"学士");
    ui->position_comboBox->addItems(QStringList()<<"教授"<<"副教授"<<"讲师"<<"助教");
    ui->men_radioButton->setChecked(true);
    ui->marry_radioButton->setChecked(true);
    ui->name_lineEdit->setText(MainWindow::teachers.num_for_teachers[change_num].name);
    ui->birth_dateEdit->setDate(MainWindow::teachers.num_for_teachers[change_num].birth);
    ui->position_comboBox->setCurrentText(MainWindow::teachers.num_for_teachers[change_num].position);
    ui->grade_comboBox->setCurrentText(MainWindow::teachers.num_for_teachers[change_num].grade);
    ui->salary_lineEdit->setText(MainWindow::teachers.num_for_teachers[change_num].salary);
    if(MainWindow::teachers.num_for_teachers[change_num].gender==true)
    {ui->men_radioButton->setChecked(true);gender=true;}
    else
    {ui->women_radioButton->setChecked(true);gender=false;}
    if(MainWindow::teachers.num_for_teachers[change_num].marry==true)
    {ui->marry_radioButton->setChecked(true);marry=true;}
    else
    {ui->nonmarry_radioButton->setChecked(true);marry=false;}
    connect(ui->men_radioButton,&QRadioButton::clicked,[=]{gender=true;});
    connect(ui->women_radioButton,&QRadioButton::clicked,[=]{gender=false;});
    connect(ui->marry_radioButton,&QRadioButton::clicked,[=]{marry=true;});
    connect(ui->nonmarry_radioButton,&QRadioButton::clicked,[=]{marry=false;});
    connect(ui->ok_pushButton,&QPushButton::clicked,this,&ChangeDialog::Change);
    connect(ui->Changecourse_pushButton,&QPushButton::clicked,
            [&]{
        EditcoursesDialog * editcourse=new EditcoursesDialog(change_num);
        int ret=editcourse->exec();
        if(ret==QDialog::Accepted)
        {
            editcourse->Edit();
            QMessageBox::about(this,"Success","修改授课信息成功!");
        }
    });
}

void ChangeDialog::Change()
{
    if(MainWindow::teachers.num_for_teachers.find(change_num)!=MainWindow::teachers.num_for_teachers.end())
    {
        MainWindow::teachers.num_for_teachers[change_num].birth=ui->birth_dateEdit->date();
        MainWindow::teachers.num_for_teachers[change_num].gender=gender;
        MainWindow::teachers.num_for_teachers[change_num].marry=marry;
        MainWindow::teachers.num_for_teachers[change_num].position=ui->position_comboBox->currentText();
        MainWindow::teachers.num_for_teachers[change_num].grade=ui->grade_comboBox->currentText();
        if(ui->name_lineEdit->text()!="")
            MainWindow::teachers.num_for_teachers[change_num].name=ui->name_lineEdit->text();
        if(ui->salary_lineEdit->text()!="")
            MainWindow::teachers.num_for_teachers[change_num].salary=ui->salary_lineEdit->text();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"警告","该编号信息不存在！");
        this->show();
    }


}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}
