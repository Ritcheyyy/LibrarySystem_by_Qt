#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <string>
#include "USEROperator.h"


namespace Ui {
class returnbook;
}

class returnbook : public QDialog
{
    Q_OBJECT

public:
    explicit returnbook(QWidget *parent = nullptr);
    ~returnbook();
    QString account;
    QString area;
    USEROperator USER;
    void returntableop();

private slots:
    void on_returnBtn_clicked();

    void on_againBtn_clicked();

private:
    Ui::returnbook *ui;
    QSqlTableModel *tm;
};

#endif // RETURNBOOK_H
