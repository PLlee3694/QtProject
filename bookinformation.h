#ifndef BOOKINFORMATION_H
#define BOOKINFORMATION_H
#include<QString>
#include<QDate>
#include"regisinfo.h"
#include<vector>
using namespace std;
class BookInformation
{
public:
    BookInformation();
    void Readbook(QTextStream &tstream);
    void Savebook(QTextStream &tstream);
    QString Datetostring();
    QString num;
    QString name;
    QDate comeOutDate;
    QString author;
    QString press;
    QString type;
    int storage;
    int page;
    vector<Regisinfo>Regisinfos;
};

#endif // BOOKINFORMATION_H
