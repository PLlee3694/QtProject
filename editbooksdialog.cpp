#include "editbooksdialog.h"
#include "ui_editbooksdialog.h"
#include"mainwindow.h"
#include<QPushButton>
#include"regisinfodialog.h"
#include"QMessageBox"
EditbooksDialog::EditbooksDialog(QString num,QWidget *parent) :
    QDialog(parent),tnum(num),
    ui(new Ui::EditbooksDialog)
{
    ui->setupUi(this);
    setWindowTitle("修改书籍登记信息");
//    setWindowIcon(QIcon(":/image/teacher-regisinfo.png"));
    setFixedSize(948,300);
    regisinfos=MainWindow::books.num_for_books[tnum].Regisinfos;
    cornum=MainWindow::books.num_for_books[tnum].storage;
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"登记编号"<<"书册名称"<<"是否已借"<<"借出时间"<<"借书证号"<<""<<"");
    ui->tableWidget->setRowCount(MainWindow::books.num_for_books[tnum].storage);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->add_pushButton,&QPushButton::clicked,
            [=]{
        addregisinfo=new RegisinfoDialog(this);
        addregisinfo->Settnum(tnum);
        int ret=addregisinfo->exec();
        if(ret==QDialog::Accepted){Addregisinfo();}});
    for(int i=0;i<MainWindow::books.num_for_books[tnum].storage;i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(QString::number(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_num)));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_name));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem((MainWindow::books.num_for_books[tnum].Regisinfos[i].borrow_or_not)));
        QString tempDate=MainWindow::books.num_for_books[tnum].Regisinfos[i].borrow_time.toString("yyyy/MM/dd");

        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(tempDate));
        ui->tableWidget->setItem(i,col++,
                                 new QTableWidgetItem(MainWindow::books.num_for_books[tnum].Regisinfos[i].card_number));
        QPushButton * butn1=new QPushButton("修改登记信息");
        QPushButton * butn2=new QPushButton("删除登记信息");
        ui->tableWidget->setCellWidget(i,col++,butn1);
        ui->tableWidget->setCellWidget(i,col++,butn2);
        connect(butn1,&QPushButton::clicked,this,&EditbooksDialog::Changeregisinfo);
        connect(butn2,&QPushButton::clicked,this,&EditbooksDialog::Deletregisinfo);
    }
}


void EditbooksDialog::Changeregisinfo()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    RegisinfoDialog * regisinfo=new RegisinfoDialog (this);
    regisinfo->setWindowTitle("修改登记信息");
    index = this->ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    regisinfo->Setnum(regisinfos[row].Regisinfo_num);
    regisinfo->Setname(regisinfos[row].Regisinfo_name);
    regisinfo->SetBorrow(regisinfos[row].borrow_or_not);
    regisinfo->SetBorrowDate(regisinfos[row].borrow_time);
    regisinfo->SetCardNum(regisinfos[row].card_number);
    int ret=regisinfo->exec();
    if(ret==QDialog::Accepted)
    {
        regisinfos[row].Regisinfo_num=regisinfo->Num();
        regisinfos[row].Regisinfo_name=regisinfo->Name();
        regisinfos[row].borrow_or_not=regisinfo->Borrow();
        regisinfos[row].borrow_time=regisinfo->BorrowDate();
        regisinfos[row].card_number=regisinfo->cardNum();
        int col=0;
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(regisinfo->Num())));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(regisinfo->Name()));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(regisinfo->Borrow()));
        QString temp= regisinfo->BorrowDate().toString("yyyy/MM/dd");
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(temp));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(regisinfo->cardNum()));
    }
}


void EditbooksDialog::Deletregisinfo()
{
    QPushButton *pushBtn = dynamic_cast<QPushButton*>(this->sender());
    if(pushBtn == 0)
        return;
    int x = pushBtn->frameGeometry().x();
    int y = pushBtn->frameGeometry().y();
    QModelIndex index;
    index = this->ui->tableWidget->indexAt(QPoint(x, y));
    int row = index.row();
    this->ui->tableWidget->removeRow(row);
    regisinfos.erase(regisinfos.begin()+row);
    cornum--;
}

void EditbooksDialog::Addregisinfo()
{
    if(addregisinfo->ifempty())
    {
        int flag=true;
        int i=0;
        for(;i<MainWindow::books.num_for_books[tnum].storage;i++)
        {
            if(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_num==addregisinfo->Num())
            {
                flag=false;
                break;
            }
        }
        if(!flag)
        {
            QString message="课程-";
            message.append(QString("%1").arg(addregisinfo->Num()));
            message.append(MainWindow::books.num_for_books[tnum].Regisinfos[i].Regisinfo_name);
            message.append("已存在");
            QMessageBox::warning(this,"警告",message);
        }
        else
        {
            Regisinfo tempregisinfo;
            tempregisinfo.Regisinfo_num=addregisinfo->Num();
            tempregisinfo.Regisinfo_name=addregisinfo->Name();
            tempregisinfo.borrow_or_not=addregisinfo->Borrow();
            tempregisinfo.borrow_time=addregisinfo->BorrowDate();
            tempregisinfo.card_number=addregisinfo->cardNum();//此处未清空添加登记信息对话框，且没有检测是否为空
            regisinfos.emplace_back(tempregisinfo);
            cornum++;
            ui->tableWidget->setRowCount(cornum);
            int col=0;
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(QString::number(addregisinfo->Num())));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addregisinfo->Name()));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addregisinfo->Borrow()));
            QString temp=addregisinfo->BorrowDate().toString();
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(temp));
            ui->tableWidget->setItem(cornum-1,col++,new QTableWidgetItem(addregisinfo->cardNum()));
            QPushButton * butn1=new QPushButton("修改登记信息");
            QPushButton * butn2=new QPushButton("删除登记信息");
            ui->tableWidget->setCellWidget(cornum-1,col++,butn1);
            ui->tableWidget->setCellWidget(cornum-1,col++,butn2);
            connect(butn1,&QPushButton::clicked,this,&EditbooksDialog::Changeregisinfo);
            connect(butn2,&QPushButton::clicked,this,&EditbooksDialog::Deletregisinfo);
        }
    }
    else
        QMessageBox::warning(this,"警告","输入信息不能为空");
}

void EditbooksDialog::Edit()
{
    MainWindow::books.num_for_books[tnum].Regisinfos.clear();
    MainWindow::books.num_for_books[tnum].Regisinfos=regisinfos;
    MainWindow::books.num_for_books[tnum].storage=cornum;
}

EditbooksDialog::~EditbooksDialog()
{
    delete ui;
}
