#ifndef EDITBOOK_H
#define EDITBOOK_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class editbook;
}

class editbook : public QDialog
{
    Q_OBJECT

public:
    explicit editbook(QDialog *parent = nullptr);
    ~editbook();
    void bookTableOP();
    QString account;

private slots:
    void on_search_clicked();

    void on_back_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::editbook *ui;
    USEROperator USER;
    QSqlTableModel *tm;
    QSqlRecord *editRec;
};

#endif // EDITBOOK_H
