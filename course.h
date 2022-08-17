#ifndef COURSE_H
#define COURSE_H
#include<QString>
#include<QTextStream>
class Course
{
public:
    Course();
    void Readcourse(QTextStream &tstream);
    void Savecourse(QTextStream &tstream);
    int course_num;
    QString course_name;
    float course_hour;
//    QString course_room;
    QString course_jiao;
    QString course_shi;
    QString course_class;
    float course_credit;
    QString course_semester;
};

#endif // COURSE_H
