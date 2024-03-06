#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "USEROperator.h"
#include "detailoperation.h"
#include "first_window_for_user.h"
#include "forgetpasswordcheck.h"
#include "first_window_for_administrator.h"

namespace Ui {
class loginwindow;
}

class loginwindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = nullptr);
    ~loginwindow();

private slots:
    void on_loginorder_clicked();

    void on_forgetBtn_clicked();

    void on_exitBtn_clicked();

private:
    Ui::loginwindow *ui;
    USEROperator USER;
    detailoperation *detail;
    first_window_for_user *fu;
    forgetpasswordcheck *fpc;
    first_window_for_Administrator *fa;
};

#endif // LOGINWINDOW_H
