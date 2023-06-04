
#ifndef DBHELPER_H
#define DBHELPER_H

#include <QtSql>
#include "widgets/nestedlistwidget.h"

class DbHelper
{
public:
    DbHelper();
    ~DbHelper();
    NestedItem getById(int id);
    bool save(NestedItem, bool);
    QVector<NestedItem> getRoot();

private:
    QSqlDatabase sdb;
};

#endif // DBHELPER_H
