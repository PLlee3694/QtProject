#include "coursesdialog.h"
#include "ui_coursesdialog.h"
#include"mainwindow.h"
CoursesDialog::CoursesDialog(QWidget *parent,QString tnum) :
    QDialog(parent),
    ui(new Ui::CoursesDialog)
{
    ui->setupUi(this);
    QString title=MainWindow::teachers.num_for_teachers[tnum].name;
    title.append(MainWindow::teachers.num_for_teachers[tnum].position);
    title.append("的授课信息");
    setWindowTitle(title);
    setWindowIcon(QIcon(":/image/course.png"));
    setFixedSize(742,300);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程编号"<<"课程名称"<<"课时"<<"授课教室"<<"授课班级"<<"学分"<<"学期");
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int cnum=MainWindow::teachers.num_for_teachers[tnum].cornum;
    ui->tableWidget->setRowCount(cnum);
    for(int i=0;i<cnum;i++)
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
    }
}

CoursesDialog::~CoursesDialog()
{
    delete ui;
}
