#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H
#include"course.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class CourseDialog;
}

class CourseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CourseDialog(QWidget *parent = nullptr);
    bool ifempty();
    void Settnum(QString);
    void Setnum(int);
    void Setname(QString);
    void Sethour(float);
    void Setjiao(QString);
    void Setshi(QString);
    void Setclass(QString);
    void Setcredit(float);
    void Setsemester(QString);
    int Num();
    QString Name();
    float Hour();
    QString Jiao();
    QString Shi();
    QString Class();
    float Credit();
    QString Semester();
    QString tnum="";
    ~CourseDialog();
private:
    Ui::CourseDialog *ui;
};

#endif // COURSEDIALOG_H
