#include "regisinfo.h"

Regisinfo::Regisinfo()
{

}

void Regisinfo::ReadRegisinfo(QTextStream &tstream)
{
    QString borrow_date_string="";
    tstream>>Regisinfo_num;
    tstream>>Regisinfo_name;
    tstream>>borrow_or_not;
    tstream>>borrow_date_string;
    tstream>>card_number;
    borrow_time=QDate::fromString(borrow_date_string,"yyyy/MM/dd");

}
void Regisinfo::SaveRegisinfo(QTextStream &tstream)
{
    tstream<<Regisinfo_num<<'\n';
    tstream<<Regisinfo_name<<'\n';
    tstream<<borrow_or_not<<"\n";
    tstream<<borrow_time.toString("yyyy/MM/dd")<<"\n";
    tstream<<card_number<<"\n";

}
