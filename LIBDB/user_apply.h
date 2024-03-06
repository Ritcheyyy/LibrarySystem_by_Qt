#ifndef USER_APPLY_H
#define USER_APPLY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlRecord>
#include "USEROperator.h"

namespace Ui {
class user_apply;
}

class user_apply : public QWidget
{
    Q_OBJECT

public:
    explicit user_apply(QWidget *parent = nullptr);
    ~user_apply();
    QString account;
    void user_applyOP();

private slots:
    void on_deleteBtn_clicked();

    void on_back_clicked();

    void on_search_clicked();

private:
    Ui::user_apply *ui;
    QSqlTableModel *tm;
    USEROperator USER;
};

#endif // USER_APPLY_H
