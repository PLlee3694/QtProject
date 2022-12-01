#ifndef EDITBOOKSDIALOG_H
#define EDITBOOKSDIALOG_H
#include"regisinfodialog.h"
#include <QDialog>
#include"mainwindow.h"
using namespace std;
namespace Ui {
class EditbooksDialog;
}

class EditbooksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditbooksDialog(QString="",QWidget *parent = nullptr);
    void Changeregisinfo();
    void Deletregisinfo();
    void Addregisinfo();
    void Edit();
    vector<Regisinfo>regisinfos;
    int cornum=0;
    RegisinfoDialog * addregisinfo;
    QString tnum;
    ~EditbooksDialog();

private:
    Ui::EditbooksDialog *ui;
};

#endif // EDITBOOKSDIALOG_H
