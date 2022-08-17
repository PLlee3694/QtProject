#include "editcoursesdialog.h"
#include "ui_editcoursesdialog.h"
#include"mainwindow.h"
#include<QPushButton>
#include"coursedialog.h"
#include"QMessageBox"
EditcoursesDialog::EditcoursesDialog(QString num,QWidget *parent) :
    QDialog(parent),tnum(num),
    ui(new Ui::EditcoursesDialog)
{
    ui->setupUi(this);
    setWindowTitle("修改教师授课信息");
    setWindowIcon(QIcon(":/image/teacher-course.png"));
    setFixedSize(948,300);
    courses=MainWindow::teachers.num_for_teachers[tnum].courses;
    cornum=MainWindow::teachers.num_for_teachers[tnum].cornum;
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"课时"<<"教室"<<"授课班级"<<"学分"<<"学期"<<""<<"");
    ui->tableWidget->setRowCount(MainWindow::teachers.num_for_teachers[tnum].cornum);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->add_pushButton,&QPushButton::clicked,
            [=]{
        addcourse=new CourseDialog(this);
        addcourse->Settnum(tnum);
        int ret=addcourse->exec();
        if(ret==QDialog::Accepted){Addcourse();}});
    for(int i=0;i<MainWindow::teachers.num_for_teachers[tnum].cornum;i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(QString::number(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_num)));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_name));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(QString("%1").arg(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_hour)));
        QString temproom=MainWindow::teachers.num_for_teachers[tnum].courses[i].course_jiao;
        temproom.append(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_shi);
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(temproom));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_class));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(QString("%1").arg(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_credit)));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_semester));
        QPushButton * butn1=new QPushButton("修改授课信息");
        QPushButton * butn2=new QPushButton("删除授课信息");
        ui->tableWidget->setCellWidget(i,col++,butn1);
        ui->tableWidget->setCellWidget(i,col++,butn2);
        connect(butn1,&QPushButton::clicked,this,&EditcoursesDialog::Changecourse);
        connect(butn2,&QPushButton::clicked,this,&EditcoursesDialog::Deletcourse);
    }
}


void EditcoursesDialog::Changecourse()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    CourseDialog * course=new CourseDialog (this);
    course->setWindowTitle("修改授课信息");
    index = this->ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    course->Setnum(courses[row].course_num);
    course->Setname(courses[row].course_name);
    course->Sethour(courses[row].course_hour);
    course->Setclass(courses[row].course_class);
    course->Setjiao(courses[row].course_jiao);
    course->Setshi(courses[row].course_shi);
    course->Setcredit(courses[row].course_credit);
    course->Setsemester(courses[row].course_semester);
    int ret=course->exec();
    if(ret==QDialog::Accepted)
    {
        courses[row].course_num=course->Num();
        courses[row].course_name=course->Name();
        courses[row].course_class=course->Class();
        courses[row].course_hour=course->Hour();
        courses[row].course_jiao=course->Jiao();
        courses[row].course_shi=course->Shi();
        courses[row].course_credit=course->Credit();
        courses[row].course_semester=course->Semester();
        int col=0;
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(course->Num())));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(course->Name()));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString("%1").arg(course->Hour())));
        QString temproom=course->Jiao();
        temproom.append(course->Shi());
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(temproom));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(course->Class()));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString("%1").arg(course->Credit())));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(course->Semester()));
    }
}


void EditcoursesDialog::Deletcourse()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    index = this->ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    this->ui->tableWidget->removeRow(row);
    courses.erase(courses.begin()+row);
    cornum--;
}

void EditcoursesDialog::Addcourse()
{
    if(addcourse->ifempty())
    {
        int flag=true;
        int i=0;
        for(;i<MainWindow::teachers.num_for_teachers[tnum].cornum;i++)
        {
            if(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_num==addcourse->Num())
            {
                flag=false;
                break;
            }
        }
        if(!flag)
        {
            QString message="课程-";
            message.append(QString("%1").arg(addcourse->Num()));
            message.append(MainWindow::teachers.num_for_teachers[tnum].courses[i].course_name);
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
            tempcourse.course_semester=addcourse->Semester();//此处未清空添加课程对话框，且没有检测是否为空
            courses.emplace_back(tempcourse);
            cornum++;
            ui->tableWidget->setRowCount(cornum);
            int col=0;
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(QString::number(addcourse->Num())));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addcourse->Name()));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(QString("%1").arg(addcourse->Hour())));
            QString temproom=addcourse->Jiao();
            temproom.append(addcourse->Shi());
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(temproom));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addcourse->Class()));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(QString("%1").arg(addcourse->Credit())));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addcourse->Semester()));
            QPushButton * butn1=new QPushButton("修改授课信息");
            QPushButton * butn2=new QPushButton("删除授课信息");
            ui->tableWidget->setCellWidget(cornum-1,col++,butn1);
            ui->tableWidget->setCellWidget(cornum-1,col++,butn2);
            connect(butn1,&QPushButton::clicked,this,&EditcoursesDialog::Changecourse);
            connect(butn2,&QPushButton::clicked,this,&EditcoursesDialog::Deletcourse);
        }
    }
    else
        QMessageBox::warning(this,"警告","输入信息不能为空");
}

void EditcoursesDialog::Edit()
{
    MainWindow::teachers.num_for_teachers[tnum].courses.clear();
    MainWindow::teachers.num_for_teachers[tnum].courses=courses;
    MainWindow::teachers.num_for_teachers[tnum].cornum=cornum;
}

EditcoursesDialog::~EditcoursesDialog()
{
    delete ui;
}
