#include "BookInformation.h"

BookInformation::BookInformation()
{

}

void BookInformation::Readbook(QTextStream &tstream)
{
    QString date_string="";
    tstream>>num;
    tstream>>name;
    tstream>>date_string;
    tstream>>type;
    tstream>>author;
    tstream>>press;
    tstream>>storage;
    tstream>>page;
    comeOutDate=QDate::fromString(date_string,"yyyy/MM/dd");

    if(storage>0)
    {
        Regisinfo tempcor;
        for(int i=0;i<storage;i++)
        {
            tempcor.ReadRegisinfo(tstream);
            Regisinfos.emplace_back(tempcor);
        }
    }
}

void BookInformation::Savebook(QTextStream &tstream)
{
    tstream<<num<<'\n';
    tstream<<name<<'\n';
    tstream<<Datetostring()<<'\n';
    tstream<<type<<'\n';
    tstream<<author<<'\n';
    tstream<<press<<'\n';
    tstream<<storage<<'\n';
    tstream<<page<<'\n';
    for(int i=0;i<storage;i++)
    {
        Regisinfos[i].SaveRegisinfo(tstream);
    }
}


QString BookInformation::Datetostring()
{
    QString date_string="";
    date_string=comeOutDate.toString("yyyy/MM/dd");
    return date_string;
}


