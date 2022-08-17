#include "teacherinformation.h"

TeacherInformation::TeacherInformation()
{

}

void TeacherInformation::Readteacher(QTextStream &tstream)
{
    QString birth_string="";
    QString gender_string="";
    QString marry_string="";
    tstream>>num;
    tstream>>name;
    tstream>>birth_string;
    tstream>>gender_string;
    tstream>>position;
    tstream>>grade;
    tstream>>salary;
    tstream>>marry_string;
    tstream>>cornum;
    birth=QDate::fromString(birth_string,"yyyy/MM/dd");
    if(gender_string=="男")
        gender=true;
    else
        gender=false;
    if(marry_string=="已婚")
        marry=true;
    else
        marry=false;
    if(cornum>0)
    {
        Course tempcor;
        for(int i=0;i<cornum;i++)
        {
            tempcor.Readcourse(tstream);
            courses.emplace_back(tempcor);
        }
    }
}

void TeacherInformation::Saveteacher(QTextStream &tstream)
{
    tstream<<num<<'\n';
    tstream<<name<<'\n';
    tstream<<Birthtostring()<<'\n';
    tstream<<Gendertostring()<<'\n';
    tstream<<position<<'\n';
    tstream<<grade<<'\n';
    tstream<<salary<<'\n';
    tstream<<Marrytostring()<<'\n';
    tstream<<cornum<<'\n';
    for(int i=0;i<cornum;i++)
    {
        courses[i].Savecourse(tstream);
    }
}

QString TeacherInformation::Gendertostring()
{
    QString gender_string="";
    if(gender==true)
        gender_string="男";
    else
        gender_string="女";
    return gender_string;
}

QString TeacherInformation::Marrytostring()
{
    QString marry_string="";
    if(marry==true)
        marry_string="已婚";
    else
        marry_string="未婚";
    return marry_string;
}

QString TeacherInformation::Birthtostring()
{
    QString birth_string="";
    birth_string=birth.toString("yyyy/MM/dd");
    return birth_string;
}

//void TeacherInformation::operator=(TeacherInformation& tmp)
//{
//    num=tmp.num;
//    name=tmp.name;
//    birth=tmp.birth;
//    gender=tmp.gender;
//    position=tmp.position;
//    grade=tmp.grade;
//    salary=tmp.salary;
//    marry=tmp.marry;
//}
