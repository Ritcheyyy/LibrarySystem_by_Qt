#ifndef READNOTICE_H
#define READNOTICE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "USEROperator.h"
#include "qdialog.h"

namespace Ui {
class readnotice;
}

class readnotice : public QWidget
{
    Q_OBJECT

public:
    explicit readnotice(QWidget *parent = nullptr);
    ~readnotice();
    void readnoticeOP();
    QString account;
    QString area;

private:
    Ui::readnotice *ui;
    USEROperator USER;
    QSqlTableModel *tm;
};

#endif // READNOTICE_H
