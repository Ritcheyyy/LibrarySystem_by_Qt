#ifndef FIRST_WINDOW_FOR_USER_H
#define FIRST_WINDOW_FOR_USER_H

#include <QDialog>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QDateTime>
#include "detailoperation.h"
#include "USEROperator.h"
#include "personalpage.h"
#include "readnotice.h"
#include "USEROperator.h"
#include "advice_for_library.h"
#include "reserveoperation.h"
#include "returnbook.h"
#include "deletereserve.h"

namespace Ui {
class first_window_for_user;
}

class first_window_for_user : public QDialog
{
    Q_OBJECT

public:
    explicit first_window_for_user(QWidget *parent = nullptr);
    ~first_window_for_user();
    QString account;
    QString area;
    void setQLable();
    void checkcredit();
    personalpage *pp;
    reserveoperation *ro;
    detailoperation *dt;
    readnotice *rn;
    returnbook *rb;
    deletereserve *dr;

private slots:
    void on_detailBtn_clicked();

    void on_setBtn_clicked();

    void on_noticeBtn_clicked();

    void on_adviceBtn_clicked();

    void on_reserveBtn_clicked();

    void on_pushButton_clicked();

    void on_borrowBtn_clicked();

    void on_myreserveBtn_clicked();

private:
    Ui::first_window_for_user *ui;
    USEROperator USER;
    advice_for_library *al;
    QPropertyAnimation *m_propertyAnimation;
    QPropertyAnimation *m_propertyAnimation2;
    bool m_bSideflag;
};

#endif // FIRST_WINDOW_FOR_USER_H
