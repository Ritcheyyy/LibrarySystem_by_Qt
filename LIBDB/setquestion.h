#ifndef SETQUESTION_H
#define SETQUESTION_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class setquestion;
}

class setquestion : public QWidget
{
    Q_OBJECT

public:
    explicit setquestion(QWidget *parent = nullptr);
    ~setquestion();
    QString account;

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::setquestion *ui;
    USEROperator USER;
};

#endif // SETQUESTION_H
