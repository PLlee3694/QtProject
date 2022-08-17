#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include"teacherinformation.h"
#include"coursedialog.h"
namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    void input();
    bool gender;
    bool marry;
    CourseDialog * addcourse;
    TeacherInformation *tempteacher;
    ~InputDialog();
signals:
    void Successfulinput();
private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
