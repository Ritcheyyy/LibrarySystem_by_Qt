#ifndef FORGET_QUESTIONCHECK_H
#define FORGET_QUESTIONCHECK_H

#include <QWidget>
#include "USEROperator.h"
#include "forgetpassword.h"
#include "forgetpasswordapply.h"

namespace Ui {
class forget_questioncheck;
}

class forget_questioncheck : public QWidget
{
    Q_OBJECT

public:
    explicit forget_questioncheck(QWidget *parent = nullptr);
    ~forget_questioncheck();
    QString account;
    QString _question;
    QString _email;
    void showOP(); // 显示密保问题

private slots:
    void on_check_clicked();

    void on_cancel_clicked();

    void on_apply_clicked();

private:
    Ui::forget_questioncheck *ui;
    USEROperator USER;
    forgetpassword *fp;
    forgetpasswordapply *fpa;
};

#endif // FORGET_QUESTIONCHECK_H
