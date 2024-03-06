#ifndef SETMAIL_H
#define SETMAIL_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class setmail;
}

class setmail : public QWidget
{
    Q_OBJECT

public:
    explicit setmail(QWidget *parent = nullptr);
    ~setmail();
    QString account;

private slots:
    void on_cancel_clicked();

    void on_ok_clicked();

private:
    Ui::setmail *ui;
    USEROperator USER;
};

#endif // SETMAIL_H
