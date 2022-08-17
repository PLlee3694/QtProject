#ifndef SCREENINGENDERDIALOG_H
#define SCREENINGENDERDIALOG_H

#include <QDialog>

namespace Ui {
class ScreeningenderDialog;
}

class ScreeningenderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeningenderDialog(QWidget *parent = nullptr);
    int Choose();
    ~ScreeningenderDialog();

private:
    Ui::ScreeningenderDialog *ui;
};

#endif // SCREENINGENDERDIALOG_H
