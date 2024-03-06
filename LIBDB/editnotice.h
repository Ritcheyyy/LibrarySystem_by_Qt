#ifndef EDITNOTICE_H
#define EDITNOTICE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "USEROperator.h"

namespace Ui {
class editnotice;
}

class editnotice : public QDialog
{
    Q_OBJECT

public:
    explicit editnotice(QDialog *parent = nullptr);
    ~editnotice();
    void noticeTableOP();
    QString account;

private slots:
    void on_newnotice_clicked();

    void on_deletenotice_clicked();

    void on_save_clicked();

private:
    Ui::editnotice *ui;
    USEROperator USER;
    QSqlTableModel *tm;
};

#endif // EDITNOTICE_H
