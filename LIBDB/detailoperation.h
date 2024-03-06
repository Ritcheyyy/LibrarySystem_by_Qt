#ifndef DETAILOPERATION_H
#define DETAILOPERATION_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QDateTime>
#include "USEROperator.h"
#include "returnbook.h"

namespace Ui {
class detailoperation;
}

class detailoperation : public QDialog
{
    Q_OBJECT

public:
    explicit detailoperation(QWidget *parent = nullptr);
    ~detailoperation();
    void bookTableOP();
    QString account;
    QString area;
    returnbook *rt;
    USEROperator USER;

private slots:
    void on_borrowBtn_clicked();
    void on_search_clicked();
    void on_back_clicked();

private:
    Ui::detailoperation *ui;
    QSqlTableModel *tm;
    returnbook *rb;
    QSqlRecord *editRec;
};

#endif // DETAILOPERATION_H
