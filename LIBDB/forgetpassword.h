#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>
#include "USEROperator.h"
#include "changepassword.h"

namespace Ui {
class forgetpassword;
}

class forgetpassword : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpassword(QWidget *parent = nullptr);
    ~forgetpassword();
    QString account;
    void showOP();

private slots:
    void on_OK_clicked();

    void on_cancel_clicked();

private:
    Ui::forgetpassword *ui;
    USEROperator USER;
    changepassword *cp;
};

#endif // FORGETPASSWORD_H
