#include "USEROperator.h"

USEROperator::USEROperator()
{   openFlag = false; }

void USEROperator::USEROpen()
{
    QString dsn;
    if(!openFlag)
    {
        dbcon = QSqlDatabase::addDatabase("QODBC");
        dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/LIBDB/userdataDB.accdb");
        dbcon.setDatabaseName(dsn);
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "错误,数据库文件打开失败！";
        openFlag = true;
    }
}

void USEROperator::USERClose()
{
    dbcon.close();
}

QSqlQuery USEROperator::USERGetData(QString sqlstr)
{
    QSqlQuery query = QSqlQuery(dbcon);
    query.exec(sqlstr);
    return query;
}
