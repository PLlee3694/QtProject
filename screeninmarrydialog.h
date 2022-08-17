#ifndef SCREENINMARRYDIALOG_H
#define SCREENINMARRYDIALOG_H

#include <QDialog>

namespace Ui {
class ScreeninmarryDialog;
}

class ScreeninmarryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeninmarryDialog(QWidget *parent = nullptr);
    int Choose();
    ~ScreeninmarryDialog();

private:
    Ui::ScreeninmarryDialog *ui;
};

#endif // SCREENINMARRYDIALOG_H
