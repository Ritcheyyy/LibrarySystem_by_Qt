#ifndef DBOPERATOR_H
#define DBOPERATOR_H

#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QDebug>

class DBOperator
{ private:
    QSqlDatabase dbcon;
    bool openFlag;
  public:
    DBOperator();
    void DBOpen();
    void DBClose();
    QSqlQuery DBGetData(QString sqlstr);
};

#endif // DBOPERATOR_H
