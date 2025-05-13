#include "DBOperator.h"

DBOperator::DBOperator()
{   openFlag = false; }

void DBOperator::DBOpen()
{   QString dsn;
    if(!openFlag)
    {   dbcon = QSqlDatabase::addDatabase("QODBC");
        dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=D:/desktop/Assignment/StudentDBPro/persondb.mdb");
        dbcon.setDatabaseName(dsn);//desktop/Assignment/StudentDBPro/
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "错误, PersonDB 数据库文件打开失败！";
        openFlag = true;
    }
}

void DBOperator::DBClose()
{   dbcon.close();
}

QSqlQuery DBOperator::DBGetData(QString sqlstr)
{   QSqlQuery query = QSqlQuery(dbcon);
    query.exec(sqlstr);
    return query;
}
