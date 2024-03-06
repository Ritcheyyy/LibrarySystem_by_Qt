#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <QWidget>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class borrow_record;
}

class borrow_record : public QWidget
{
    Q_OBJECT

public:
    explicit borrow_record(QWidget *parent = nullptr);
    ~borrow_record();
    USEROperator USER;
    void recordtableop();

private slots:
    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void on_saveBtn_clicked();

    void on_search_clicked();

    void on_back_clicked();

private:
    Ui::borrow_record *ui;
    QSqlTableModel *tm;
};

#endif // BORROW_RECORD_H
