#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    void Login_Success();
    void user_login_success();
    ~LoginDialog();

signals:
    void Showmainwindow();
    void Showmainwindow2();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
