#ifndef TEACHERINFORMATIONTABLE_H
#define TEACHERINFORMATIONTABLE_H
#include<vector>
#include"teacherinformation.h"
#include<QString>
//#include<unordered_map>
#include<QHash>
using namespace std;
class TeacherInformationTable
{
public:
    TeacherInformationTable();
    bool Readteacherfromfile(const QString &readfilename);
    bool Saveteachertofile(const QString &savefilename);
    QHash<QString,TeacherInformation>num_for_teachers;
    int tnum;
};

#endif // TEACHERINFORMATIONTABLE_H
