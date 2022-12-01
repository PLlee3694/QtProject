#include "changedialog.h"
#include "ui_changedialog.h"
#include"mainwindow.h"
#include<QMessageBox>
#include"editbooksdialog.h"
ChangeDialog::ChangeDialog(QWidget *parent,QString num) :
    QDialog(parent),borrow(true),
    ui(new Ui::ChangeDialog),change_num(num)
{
    ui->setupUi(this);
    setWindowTitle("修改书籍信息");
    setWindowIcon(QIcon(":/image/mainwindow.png"));
    setFixedSize(260,443);
    ui->type_comboBox->addItems(QStringList()<<"小说"<<"科普"<<"教科书"<<"其他");
    ui->name_lineEdit->setText(MainWindow::books.num_for_books[change_num].name);
    ui->author_lineEdit->setText(MainWindow::books.num_for_books[change_num].author);
    ui->birth_dateEdit->setDate(MainWindow::books.num_for_books[change_num].comeOutDate);
    ui->press_lineEdit->setText(MainWindow::books.num_for_books[change_num].press);
    ui->type_comboBox->setCurrentText(MainWindow::books.num_for_books[change_num].type);
    ui->storage_lineEdit->setText(QString::number(MainWindow::books.num_for_books[change_num].storage));
    ui->page_lineEdit->setText(QString::number(MainWindow::books.num_for_books[change_num].page));
    connect(ui->ok_pushButton,&QPushButton::clicked,this,&ChangeDialog::Change);
    connect(ui->Changeregis_pushButton,&QPushButton::clicked,
            [&]{
        EditbooksDialog * editbook=new EditbooksDialog(change_num);
        int ret=editbook->exec();
        if(ret==QDialog::Accepted)
        {
            editbook->Edit();
            QMessageBox::about(this,"Success","修改登记信息成功!");
        }
    });
}

void ChangeDialog::Change()
{
    if(MainWindow::books.num_for_books.find(change_num)!=MainWindow::books.num_for_books.end())
    {
        MainWindow::books.num_for_books[change_num].comeOutDate=ui->birth_dateEdit->date();
        MainWindow::books.num_for_books[change_num].author=ui->author_lineEdit->text();
        MainWindow::books.num_for_books[change_num].type=ui->type_comboBox->currentText();
        MainWindow::books.num_for_books[change_num].press=ui->press_lineEdit->text();
        if(ui->name_lineEdit->text()!="")
            MainWindow::books.num_for_books[change_num].name=ui->name_lineEdit->text();
        if(ui->storage_lineEdit->text()!="")
            MainWindow::books.num_for_books[change_num].storage=ui->storage_lineEdit->text().toInt();
        if(ui->page_lineEdit->text()!="")
            MainWindow::books.num_for_books[change_num].page=ui->page_lineEdit->text().toInt();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"警告","该编号信息不存在！");
        this->show();
    }


}

ChangeDialog::~ChangeDialog()
{
    delete ui;
}
