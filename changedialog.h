#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H
#include"regisinfosdialog.h"
#include <QDialog>

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDialog(QWidget *parent = nullptr,QString num="");
    void Change();
    bool borrow;
    ~ChangeDialog();

private:
    Ui::ChangeDialog *ui;
    QString change_num;
};

#endif // CHANGEDIALOG_H
