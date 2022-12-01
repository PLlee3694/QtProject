#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include"bookinformation.h"
#include"regisinfodialog.h"
namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    void input();
    bool borrow;
    RegisinfoDialog * addRegisinfo;
    BookInformation *tempbook;
    ~InputDialog();
signals:
    void Successfulinput();
private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
