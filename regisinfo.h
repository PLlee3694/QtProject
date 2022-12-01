#ifndef REGISINFO_H
#define REGISINFO_H
#include<QString>
#include<QDate>
#include<QTextStream>
class Regisinfo
{
public:
    Regisinfo();
    void ReadRegisinfo(QTextStream &tstream);
    void SaveRegisinfo(QTextStream &tstream);
    int Regisinfo_num;
    QString Regisinfo_name;
    QDate borrow_time;
    QString card_number;
    QString borrow_or_not;
};

#endif // REGISINFO_H
