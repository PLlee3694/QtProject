#include "inputdialog.h"
#include "ui_inputdialog.h"
#include"bookinformation.h"
#include"bookinformationtable.h"
#include"mainwindow.h"
#include<QMessageBox>
#include"regisinfodialog.h"
InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),borrow(true),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    setWindowTitle("新建书籍信息");
    setWindowIcon(QIcon(":/image/teacher-course.png"));
    setFixedSize(260,443);
    tempbook=new BookInformation();
    ui->ok_pushButton->setFocus();
    ui->grade_comboBox->addItems(QStringList()<<"小说"<<"科普"<<"教材"<<"其他");
    connect(ui->ok_pushButton,&QPushButton::clicked,this,&InputDialog::input);
    connect(ui->Addregis_pushButton,&QPushButton::clicked,
            [=]{
        addRegisinfo=new RegisinfoDialog (this);
        addRegisinfo->Settnum(ui->num_lineEdit->text());
        int ret=addRegisinfo->exec();
        if(ret==QDialog::Accepted)
        {
            if(addRegisinfo->ifempty())
            {
                int flag=true;
                for(int i=0;i<tempbook->storage;i++)
                {
                    if(tempbook->Regisinfos[i].Regisinfo_num==addRegisinfo->Num())
                    {
                        flag=false;
                        break;
                    }
                }
                if(!flag)
                {
                    QString message="登记信息-";
                    message.append(QString("%1").arg(addRegisinfo->Num()));
                    for(int i=0;i<tempbook->storage;i++)
                    {
                       if(addRegisinfo->Num()==tempbook->Regisinfos[i].Regisinfo_num)
                           message.append(tempbook->Regisinfos[i].Regisinfo_name);
                    }
                    message.append("已存在");
                    QMessageBox::warning(this,"警告",message);
                }
                else
                {
                    Regisinfo tempRegisinfo;
                    tempRegisinfo.Regisinfo_num=addRegisinfo->Num();
                    tempRegisinfo.Regisinfo_name=addRegisinfo->Name();
                    tempRegisinfo.borrow_or_not=addRegisinfo->Borrow();
                    tempRegisinfo.borrow_time=addRegisinfo->BorrowDate();
                    tempRegisinfo.card_number=addRegisinfo->cardNum();
                    tempbook->Regisinfos.emplace_back(tempRegisinfo);
                    tempbook->storage++;
                    QMessageBox::about(this,"Success","添加登记信息成功(确认添加书籍信息后保存)");
                }
            }
            else
                QMessageBox::warning(this,"警告","输入信息不能为空");
        }
    });
}

void InputDialog::input()
{
    if(
            ui->num_lineEdit->text()!=""&&
            ui->name_lineEdit->text()!=""&&
            ui->salary_lineEdit->text()!=""
            )
    {
        if(MainWindow::books.num_for_books.find(ui->num_lineEdit->text())==MainWindow::books.num_for_books.end())
        {
            tempbook->num=ui->num_lineEdit->text();
            tempbook->name=ui->name_lineEdit->text();
            tempbook->comeOutDate=ui->birth_dateEdit->date();
            tempbook->press=ui->press_lineEdit->text();
            tempbook->author=ui->lineEdit->text();
            tempbook->type=ui->grade_comboBox->currentText();
            tempbook->storage=ui->salary_lineEdit->text().toInt();
            tempbook->page=ui->page_lineEdit->text().toInt();
            MainWindow::books.num_for_books[tempbook->num]=*tempbook;
            MainWindow::books.tnum++;
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"警告","该编号信息已存在！");
            this->show();
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","请重新检查输入，信息不能为空！");
        this->show();
    }
}

InputDialog::~InputDialog()
{
    delete ui;
}
