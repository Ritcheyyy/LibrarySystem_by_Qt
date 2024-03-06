#ifndef FIRST_WINDOW_FOR_ADMINISTRATOR_H
#define FIRST_WINDOW_FOR_ADMINISTRATOR_H

#include <QWidget>
#include <QPropertyAnimation>
#include "edituser.h"
#include "editbook.h"
#include "editnotice.h"
#include "check_admini.h"
#include "dealapply.h"
#include "user_apply.h"
#include "borrow_record.h"
#include "personalpage.h"
#include "USEROperator.h"

namespace Ui {
class first_window_for_Administrator;
}

class first_window_for_Administrator : public QWidget
{
    Q_OBJECT

public:
    explicit first_window_for_Administrator(QWidget *parent = nullptr);
    ~first_window_for_Administrator();
    QString account;
    void setQLable();

private slots:
    void on_noticeBtn_clicked();

    void on_checkBtn_clicked();

    void on_detailBtn_clicked();

    void on_editBtn_clicked();

    void on_checkBtn_2_clicked();

    void on_setBtn_clicked();

    void on_checkBtn_3_clicked();

    void on_pushButton_clicked();

    void on_borrowBtn_clicked();

private:
    Ui::first_window_for_Administrator *ui;
    edituser *eu;
    editbook *eb;
    editnotice *en;
    check_admini *ca;
    dealapply *da;
    personalpage *pp;
    user_apply *ua;
    borrow_record *br;
    USEROperator USER;
    QPropertyAnimation *m_propertyAnimation;
    QPropertyAnimation *m_propertyAnimation2;
    bool m_bSideflag;
};

#endif // FIRST_WINDOW_FOR_ADMINISTRATOR_H
