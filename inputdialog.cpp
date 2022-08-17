#include "inputdialog.h"
#include "ui_inputdialog.h"
#include"teacherinformation.h"
#include"teacherinformationtable.h"
#include"mainwindow.h"
#include<QMessageBox>
#include"coursedialog.h"
InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),gender(true),marry(true),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    setWindowTitle("新建教师信息");
    setWindowIcon(QIcon(":/image/teacher-course.png"));
    setFixedSize(260,443);
    tempteacher=new TeacherInformation();
    ui->men_radioButton->setChecked(true);
    ui->marry_radioButton->setChecked(true);
    ui->ok_pushButton->setFocus();
    ui->grade_comboBox->addItems(QStringList()<<"博士"<<"硕士"<<"学士");
    ui->position_comboBox->addItems(QStringList()<<"教授"<<"副教授"<<"讲师"<<"助教");
    connect(ui->men_radioButton,&QRadioButton::clicked,[=]{gender=true;});
    connect(ui->women_radioButton,&QRadioButton::clicked,[=]{gender=false;});
    connect(ui->marry_radioButton,&QRadioButton::clicked,[=]{marry=true;});
    connect(ui->nonmarry_radioButton,&QRadioButton::clicked,[=]{marry=false;});
    connect(ui->ok_pushButton,&QPushButton::clicked,this,&InputDialog::input);
    connect(ui->Addcourse_pushButton,&QPushButton::clicked,
            [=]{
        addcourse=new CourseDialog (this);
        addcourse->Settnum(ui->num_lineEdit->text());
        int ret=addcourse->exec();
        if(ret==QDialog::Accepted)
        {
            if(addcourse->ifempty())
            {
                int flag=true;
                for(int i=0;i<tempteacher->cornum;i++)
                {
                    if(tempteacher->courses[i].course_num==addcourse->Num())
                    {
                        flag=false;
                        break;
                    }
                }
                if(!flag)
                {
                    QString message="课程-";
                    message.append(QString("%1").arg(addcourse->Num()));
                    for(int i=0;i<tempteacher->cornum;i++)
                    {
                       if(addcourse->Num()==tempteacher->courses[i].course_num)
                           message.append(tempteacher->courses[i].course_name);
                    }
                    message.append("已存在");
                    QMessageBox::warning(this,"警告",message);
                }
                else
                {
                    Course tempcourse;
                    tempcourse.course_num=addcourse->Num();
                    tempcourse.course_name=addcourse->Name();
                    tempcourse.course_hour=addcourse->Hour();
                    tempcourse.course_jiao=addcourse->Jiao();
                    tempcourse.course_shi=addcourse->Shi();
                    tempcourse.course_class=addcourse->Class();
                    tempcourse.course_credit=addcourse->Credit();
                    tempcourse.course_semester=addcourse->Semester();
                    tempteacher->courses.emplace_back(tempcourse);
                    tempteacher->cornum++;
                    QMessageBox::about(this,"Success","添加课程成功(确认添加教师信息后保存)");
                }
            }
            else
                QMessageBox::warning(this,"警告","输入信息不能为空");
        }
    });
}

void InputDialog::input()
{
    if(
            ui->num_lineEdit->text()!=""&&
            ui->name_lineEdit->text()!=""&&
            ui->salary_lineEdit->text()!=""
            )
    {
        if(MainWindow::teachers.num_for_teachers.find(ui->num_lineEdit->text())==MainWindow::teachers.num_for_teachers.end())
        {
            tempteacher->num=ui->num_lineEdit->text();
            tempteacher->name=ui->name_lineEdit->text();
            tempteacher->birth=ui->birth_dateEdit->date();
            tempteacher->gender=gender;
            tempteacher->position=ui->position_comboBox->currentText();
            tempteacher->grade=ui->grade_comboBox->currentText();
            tempteacher->salary=ui->salary_lineEdit->text();
            tempteacher->marry=marry;
            MainWindow::teachers.num_for_teachers[tempteacher->num]=*tempteacher;
            MainWindow::teachers.tnum++;
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"警告","该编号信息已存在！");
            this->show();
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","请重新检查输入，信息不能为空！");
        this->show();
    }
}

InputDialog::~InputDialog()
{
    delete ui;
}
