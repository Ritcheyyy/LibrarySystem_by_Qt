#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class edituser;
}

class edituser : public QDialog
{
    Q_OBJECT

public:
    explicit edituser(QDialog *parent = nullptr);
    ~edituser();
    void userTableOP();
    QString account;

private slots:
    void on_back_clicked();

    void on_search_clicked();

    void on_deleteBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::edituser *ui;
    USEROperator USER;
    QSqlTableModel *tm;
    QSqlRecord *editRec;
};

#endif // EDITUSER_H
