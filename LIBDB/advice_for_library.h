#ifndef ADVICE_FOR_LIBRARY_H
#define ADVICE_FOR_LIBRARY_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "USEROperator.h"


namespace Ui {
class advice_for_library;
}

class advice_for_library : public QWidget
{
    Q_OBJECT

public:
    explicit advice_for_library(QWidget *parent = nullptr);
    ~advice_for_library();
    QString account;

private slots:
    void on_submit_clicked();

private:
    Ui::advice_for_library *ui;
    USEROperator USER;
};

#endif // ADVICE_FOR_LIBRARY_H
