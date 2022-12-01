#ifndef REGISINFOSDIALOG_H
#define REGISINFOSDIALOG_H

#include <QDialog>

namespace Ui {
class RegisinfosDialog;
}

class RegisinfosDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisinfosDialog(QWidget *parent = nullptr,QString="");
    ~RegisinfosDialog();

private:
    Ui::RegisinfosDialog *ui;
};

#endif // REGISINFOSDIALOG_H
