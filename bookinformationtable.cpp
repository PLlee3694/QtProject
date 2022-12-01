#include "BookInformationtable.h"
#include<QFile>
#include<QTextStream>
#include"mainwindow.h"
BookInformationTable::BookInformationTable():tnum(0)
{

}
bool BookInformationTable::Readbookfromfile(const QString &readfilename)
{
    QFile myfile(readfilename);
    if(!myfile.exists())
        return false;
    if(!myfile.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    QTextStream mystream(&myfile);
    num_for_books.clear();
    tnum=0;
    mystream>>tnum;
    QString tempnum="";
    BookInformation tempbook;
    if(tnum>0)
    {
        for(int i=0;i<tnum;i++)
        {
            mystream>>tempnum;
            num_for_books[tempnum].Readbook(mystream);
        }
    }
    myfile.close();
    return true;
}

bool BookInformationTable::Savebooktofile(const QString &savefilename)
{
    QFile myfile(savefilename);
    if(!myfile.open(QIODevice::WriteOnly|QIODevice::Text))
        return false;
    QTextStream mystream(&myfile);
    mystream<<tnum<<'\n';
    if(tnum>0)
    {
        for(auto i=MainWindow::books.num_for_books.begin();i!=MainWindow::books.num_for_books.end();i++)
        {
            mystream<<i->first<<"\n";
            i->second.Savebook(mystream);
        }
    }
    myfile.close();
    return true;
}
