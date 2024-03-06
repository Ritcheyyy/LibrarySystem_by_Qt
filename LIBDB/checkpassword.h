#ifndef CHECKPASSWORD_H
#define CHECKPASSWORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include "personalpage.h"
#include "USEROperator.h"
#include "setquestion.h"
#include "setmail.h"
#include "first_window_for_user.h"

namespace Ui {
class checkpassword;
}

class checkpassword : public QWidget
{
    Q_OBJECT

public:
    explicit checkpassword(QWidget *parent = nullptr);
    ~checkpassword();
    personalpage *pp;
    QString account;
    int flag;
    first_window_for_user *fu;

private slots:
    void on_ok_clicked();

private:
    Ui::checkpassword *ui;
    USEROperator USER;
    setquestion *sq;
    setmail *sm;
};

#endif // CHECKPASSWORD_H
