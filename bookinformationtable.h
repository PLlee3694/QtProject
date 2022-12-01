#ifndef BOOKINFORMATIONTABLE_H
#define BOOKINFORMATIONTABLE_H
#include<vector>
#include"bookinformation.h"
#include<QString>
#include<unordered_map>
using namespace std;
class BookInformationTable
{
public:
    BookInformationTable();
    bool Readbookfromfile(const QString &readfilename);
    bool Savebooktofile(const QString &savefilename);
    unordered_map<QString,BookInformation>num_for_books;
    int tnum;
};

#endif // BOOKINFORMATIONTABLE_H
