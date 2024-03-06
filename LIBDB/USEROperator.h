#ifndef USEROPERATOR_H
#define USEROPERATOR_H

#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QDebug>

class USEROperator
{
  public:
    QSqlDatabase dbcon;
    bool openFlag;
    USEROperator();
    void USEROpen();
    void USERClose();
    QSqlQuery USERGetData(QString sqlstr);
};

#endif // USEROPERATOR_H
