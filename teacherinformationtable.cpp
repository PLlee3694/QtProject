#include "teacherinformationtable.h"
#include<QFile>
#include<QTextStream>
#include"mainwindow.h"
TeacherInformationTable::TeacherInformationTable():tnum(0)
{

}
bool TeacherInformationTable::Readteacherfromfile(const QString &readfilename)
{
    QFile myfile(readfilename);
    if(!myfile.exists())
        return false;
    if(!myfile.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    QTextStream mystream(&myfile);
    num_for_teachers.clear();
    tnum=0;
    mystream>>tnum;
    QString tempnum="";
    TeacherInformation tempteacher;
    if(tnum>0)
    {
        for(int i=0;i<tnum;i++)
        {
            mystream>>tempnum;
            num_for_teachers[tempnum].Readteacher(mystream);
        }
    }
    myfile.close();
    return true;
}

bool TeacherInformationTable::Saveteachertofile(const QString &savefilename)
{
    QFile myfile(savefilename);
    if(!myfile.open(QIODevice::WriteOnly|QIODevice::Text))
        return false;
    QTextStream mystream(&myfile);
    mystream<<tnum<<'\n';
    if(tnum>0)
    {
        for(auto i=MainWindow::teachers.num_for_teachers.begin();i!=MainWindow::teachers.num_for_teachers.end();i++)
        {
            mystream<<i.key()<<"\n";
            i.value().Saveteacher(mystream);
        }
    }
    myfile.close();
    return true;
}
