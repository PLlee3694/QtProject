#include "course.h"

Course::Course()
{

}

void Course::Readcourse(QTextStream &tstream)
{
    tstream>>course_num;
    tstream>>course_name;
    tstream>>course_hour;
    tstream>>course_jiao;
    tstream>>course_shi;
    tstream>>course_class;
    tstream>>course_credit;
    tstream>>course_semester;
}
void Course::Savecourse(QTextStream &tstream)
{
    tstream<<course_num<<'\n';
    tstream<<course_name<<'\n';
    tstream<<course_hour<<'\n';
    tstream<<course_jiao<<'\n';
    tstream<<course_shi<<'\n';
    tstream<<course_class<<'\n';
    tstream<<course_credit<<'\n';
    tstream<<course_semester<<'\n';
}
