#ifndef BORROBYNAMEDIALOG_H
#define BORROBYNAMEDIALOG_H


#include <QDialog>
#include<QString>
namespace Ui {
class borrowbynameDialog;
}

class borrowbynameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit borrowbynameDialog(QWidget *parent = nullptr);
    QString bookname();
    ~borrowbynameDialog();

private:
    Ui::borrowbynameDialog *ui;
};
#endif // BORROBYNAMEDIALOG_H
