#ifndef FORGETPASSWORDAPPLY_H
#define FORGETPASSWORDAPPLY_H

#include <QWidget>
#include "USEROperator.h"

namespace Ui {
class forgetpasswordapply;
}

class forgetpasswordapply : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpasswordapply(QWidget *parent = nullptr);
    ~forgetpasswordapply();
    QString account;
    QString schoolnum;
    QString name;
    QString _question;
    void showOP();
private slots:
    void on_submit_clicked();

    void on_cancel_clicked();


private:
    Ui::forgetpasswordapply *ui;
    USEROperator USER;
};

#endif // FORGETPASSWORDAPPLY_H
