#ifndef DETAILOPERATION_FOR_VISITOR_H
#define DETAILOPERATION_FOR_VISITOR_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include "USEROperator.h"
#include "registerwindow.h"

namespace Ui {
class detailoperation_for_visitor;
}

class detailoperation_for_visitor : public QDialog
{
    Q_OBJECT

public:
    explicit detailoperation_for_visitor(QWidget *parent = nullptr);
    ~detailoperation_for_visitor();
    void bookTableOP();
    QString account;

private slots:
    void on_search_clicked();
    void on_back_clicked();

    void on_registerBtn_clicked();

private:
    Ui::detailoperation_for_visitor *ui;
    USEROperator USER;
    QSqlTableModel *tm;
    QSqlRecord *editRec;
    registerwindow *rw;
};

#endif // DETAILOPERATION_FOR_VISITOR_H
