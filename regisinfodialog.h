#ifndef REGISINFODIALOG_H
#define REGISINFODIALOG_H
#include"regisinfo.h"
#include <QDialog>
#include"mainwindow.h"
namespace Ui {
class RegisinfoDialog;
}

class RegisinfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegisinfoDialog(QWidget *parent = nullptr);
    bool ifempty();
    void Settnum(QString);
    void Setnum(int);
    void Setname(QString);
    void SetBorrow(QString);
    void SetBorrowDate(QDate);
    void SetCardNum(QString);

    int Num();
    QString Name();
    QString Borrow();
    QDate BorrowDate();
    QString cardNum();
    QString tnum="";
    ~RegisinfoDialog();
private:
    Ui::RegisinfoDialog *ui;
};

#endif // REGISINFODIALOG_H
