#include "DBOperator.h"

DBOperator::DBOperator()
{   openFlag = false; }

void DBOperator::DBOpen()
{   QString dsn;
    if(!openFlag)
    {   dbcon = QSqlDatabase::addDatabase("QODBC");
        dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=D:/desktop/Assignment/SQLTest/SQLDB.mdb");
        dbcon.setDatabaseName(dsn);
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "错误, SQLDB 数据库文件打开失败！";
        openFlag = true;
    }
}

void DBOperator::DBClose()
{   openFlag = false;
    dbcon.close();
}

QSqlQuery DBOperator::DBGetData(QString sqlstr, bool &sucessFlag)
{   QSqlQuery query = QSqlQuery(dbcon);
    sucessFlag = query.exec(sqlstr);
    return query;
}
