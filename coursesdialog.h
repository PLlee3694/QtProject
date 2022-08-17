#ifndef COURSESDIALOG_H
#define COURSESDIALOG_H

#include <QDialog>

namespace Ui {
class CoursesDialog;
}

class CoursesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoursesDialog(QWidget *parent = nullptr,QString="");
    ~CoursesDialog();

private:
    Ui::CoursesDialog *ui;
};

#endif // COURSESDIALOG_H
