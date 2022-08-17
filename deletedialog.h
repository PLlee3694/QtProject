#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr,QString title="输入教师编号以删除教师信息");
    ~DeleteDialog();
    QString Num();
signals:
    void Successfuldelete();
private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
