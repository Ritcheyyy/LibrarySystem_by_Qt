#ifndef DELETERESERVE_H
#define DELETERESERVE_H

#include <QWidget>
#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <string>
#include "USEROperator.h"

namespace Ui {
class deletereserve;
}

class deletereserve : public QWidget
{
    Q_OBJECT

public:
    explicit deletereserve(QWidget *parent = nullptr);
    ~deletereserve();
    QString account;
    QString area;
    USEROperator USER;
    void deletereservetableop();

private slots:

    void on_returnBtn_clicked();

private:
    Ui::deletereserve *ui;
    QSqlTableModel *tm;
};

#endif // DELETERESERVE_H
