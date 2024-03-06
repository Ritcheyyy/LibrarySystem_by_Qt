#ifndef CHECK_ADMINI_H
#define CHECK_ADMINI_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include "USEROperator.h"

namespace Ui {
class check_admini;
}

class check_admini : public QDialog
{
    Q_OBJECT

public:
    explicit check_admini(QWidget *parent = nullptr);
    ~check_admini();
    QString account;
    void checkTableOP();

private slots:
    void on_back_clicked();

    void on_search_clicked();

    void on_deleteBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::check_admini *ui;
    USEROperator USER;
    QSqlTableModel *tm;
};

#endif // CHECK_ADMINI_H
