#ifndef SCREENINGRADEDIALOG_H
#define SCREENINGRADEDIALOG_H

#include <QDialog>

namespace Ui {
class ScreeningradeDialog;
}

class ScreeningradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeningradeDialog(QWidget *parent = nullptr);
    int Choose();
    ~ScreeningradeDialog();

private:
    Ui::ScreeningradeDialog *ui;
};

#endif // SCREENINGRADEDIALOG_H
