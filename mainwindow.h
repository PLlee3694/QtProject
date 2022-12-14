#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"logindialog.h"
#include <QMainWindow>
#include<QFileDialog>
#include"bookinformationtable.h"
#include<unordered_map>
#include<QLabel>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Update();
    void Closethewidget();
    void Showregis();
    static BookInformationTable books;
    static QString user_num;
    QLabel * Labeltnum;
    ~MainWindow();

signals:
    void return_to_the_login();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
