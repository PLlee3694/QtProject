#ifndef SCREENINPOSITIONDIALOG_H
#define SCREENINPOSITIONDIALOG_H

#include <QDialog>

namespace Ui {
class ScreeninpositionDialog;
}

class ScreeninpositionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScreeninpositionDialog(QWidget *parent = nullptr);
    int Choose();
    ~ScreeninpositionDialog();

private:
    Ui::ScreeninpositionDialog *ui;
};

#endif // SCREENINPOSITIONDIALOG_H
