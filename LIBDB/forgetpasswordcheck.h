#ifndef FORGETPASSWORDCHECK_H
#define FORGETPASSWORDCHECK_H

#include <QWidget>
#include "USEROperator.h"
#include "forget_questioncheck.h"
#include "user_apply.h"

namespace Ui {
class forgetpasswordcheck;
}

class forgetpasswordcheck : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpasswordcheck(QWidget *parent = nullptr);
    ~forgetpasswordcheck();
    QString account;
    void showOP();

private slots:
    void on_check_clicked();

    void on_cancel_clicked();

private:
    Ui::forgetpasswordcheck *ui;
    forget_questioncheck *fqc;
    user_apply *ua;
    USEROperator USER;
    forgetpassword *fp;
};

#endif // FORGETPASSWORDCHECK_H
