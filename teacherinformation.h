    #ifndef TEACHERINFORMATION_H
#define TEACHERINFORMATION_H
#include<QString>
#include<QDate>
#include"course.h"
#include<vector>
using namespace std;
class TeacherInformation
{
public:
    TeacherInformation();
    void Readteacher(QTextStream &tstream);
    void Saveteacher(QTextStream &tstream);
//    void operator=(TeacherInformation&);
    QString Birthtostring();
    QString Gendertostring();
    QString Marrytostring();
    QString num;
    QString name;
    QDate birth;
    bool gender;
    QString position;
    QString grade;
    QString salary;
    bool marry;
    int cornum=0;
    vector<Course>courses;
};

#endif // TEACHERINFORMATION_H
