#ifndef RESERVEOPERATION_H
#define RESERVEOPERATION_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QSqlRecord>
#include <QDateTime>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class reserveoperation;
}

class reserveoperation : public QDialog
{
    Q_OBJECT

public:
    explicit reserveoperation(QWidget *parent = nullptr);
    ~reserveoperation();
    QString account;
    QString area;
    void reserveTableOP();
    USEROperator USER;

private slots:
    void on_borrowBtn_clicked();
    void on_search_clicked();
    void on_back_clicked();

private:
    Ui::reserveoperation *ui;
    QSqlTableModel *tm;
    QSqlRecord *editRec;
};

#endif // RESERVEOPERATION_H
