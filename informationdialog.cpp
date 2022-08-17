#include "informationdialog.h"
#include "ui_informationdialog.h"
#include"mainwindow.h"
InformationDialog::InformationDialog(QWidget *parent,QString num) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    resize(300,360);
    QString title=MainWindow::teachers.num_for_teachers[num].name;
    title.append(MainWindow::teachers.num_for_teachers[num].position);
    title.append("的信息");
    setWindowTitle(title);
    setWindowIcon(QIcon(":/image/teacher-course.png"));
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->baseinfo_pushButton,&QPushButton::clicked,[=]{ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->courseinfo_pushButton,&QPushButton::clicked,[=]{ui->stackedWidget->setCurrentIndex(1);});
    ui->tableWidget->setRowCount(8);
    ui->tableWidget->setVerticalHeaderLabels(QStringList()<<"编号"<<"姓名"<<"性别"<<"出生日期"<<"职称"<<"学历"<<"工资"<<"婚否");
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QString gender;
    if(MainWindow::teachers.num_for_teachers[num].gender)
        gender="男";
    else
        gender="女";
    QString marry;
    if(MainWindow::teachers.num_for_teachers[num].marry)
        marry="已婚";
    else
        marry="未婚";
    int row=0;
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(num));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].name));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(gender));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(QString(MainWindow::teachers.num_for_teachers[num].birth.toString("yyyy/MM/dd"))));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].position));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].grade));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].salary));
    ui->tableWidget->setItem(row++,0,new QTableWidgetItem(marry));
    ui->tableWidget_2->setRowCount(7);
    ui->tableWidget_2->setVerticalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"课时"<<"授课教室"<<"授课班级"<<"学分"<<"学期");
    int cnum=MainWindow::teachers.num_for_teachers[num].cornum;
    ui->tableWidget_2->setColumnCount(cnum);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<cnum;i++)
    {
        int row=0;
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(QString::number(MainWindow::teachers.num_for_teachers[num].courses[i].course_num)));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].courses[i].course_name));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(QString("%1").arg(MainWindow::teachers.num_for_teachers[num].courses[i].course_hour)));
        QString temproom=MainWindow::teachers.num_for_teachers[num].courses[i].course_jiao;
        temproom.append(MainWindow::teachers.num_for_teachers[num].courses[i].course_shi);
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(temproom));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].courses[i].course_class));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(QString("%1").arg(MainWindow::teachers.num_for_teachers[num].courses[i].course_credit)));
        ui->tableWidget_2->setItem(row++,i,
                                 new QTableWidgetItem(MainWindow::teachers.num_for_teachers[num].courses[i].course_semester));
    }
}

InformationDialog::~InformationDialog()
{
    delete ui;
}
