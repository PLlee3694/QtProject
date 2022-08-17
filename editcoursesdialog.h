#ifndef EDITCOURSESDIALOG_H
#define EDITCOURSESDIALOG_H
#include"coursedialog.h"
#include <QDialog>
#include"mainwindow.h"
using namespace std;
namespace Ui {
class EditcoursesDialog;
}

class EditcoursesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditcoursesDialog(QString="",QWidget *parent = nullptr);
    void Changecourse();
    void Deletcourse();
    void Addcourse();
    void Edit();
    vector<Course>courses;
    int cornum=0;
    CourseDialog * addcourse;
    QString tnum;
    ~EditcoursesDialog();

private:
    Ui::EditcoursesDialog *ui;
};

#endif // EDITCOURSESDIALOG_H
