#ifndef SCREENINBIRTHDIALOG_H
#define SCREENINBIRTHDIALOG_H

#include <QDialog>

namespace Ui {
class ScreeninbirthDialog;
}

class ScreeninbirthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeninbirthDialog(QWidget *parent = nullptr);
    QDate Time();
    bool Choose();
    ~ScreeninbirthDialog();

private:
    Ui::ScreeninbirthDialog *ui;
};

#endif // SCREENINBIRTHDIALOG_H
