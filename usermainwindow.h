#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include"logindialog.h"
#include <QMainWindow>
#include<QFileDialog>
#include"bookinformationtable.h"
#include<unordered_map>
#include<QLabel>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class UserMainWindow; }
QT_END_NAMESPACE

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    UserMainWindow(QWidget *parent = nullptr);
    void Update();
    void Closethewidget();
    void Showregis();
//    void Screeninbirth(QDate,bool);
//    void Screeninposition(int);
//    void Screeningrade(int);
//    void Screeningender(int);
//    void Screeninmarry(int);
    static BookInformationTable books;
    static QString user_num;
    QLabel * Labeltnum;
    ~UserMainWindow();

signals:
    void return_to_the_login();

private:
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
