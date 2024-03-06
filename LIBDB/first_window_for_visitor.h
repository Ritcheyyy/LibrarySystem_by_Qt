#ifndef FIRST_WINDOW_FOR_VISITOR_H
#define FIRST_WINDOW_FOR_VISITOR_H

#include <QDialog>
#include <QPropertyAnimation>
#include "detailoperation_for_visitor.h"
#include "registerwindow.h"
#include "readnotice.h"
#include "USEROperator.h"

namespace Ui {
class first_window_for_visitor;
}

class first_window_for_visitor : public QDialog
{
    Q_OBJECT

public:
    explicit first_window_for_visitor(QWidget *parent = nullptr);
    ~first_window_for_visitor();
    void setQLable();

private slots:
    void on_detailBtn_clicked();

    void on_registerBtn_clicked();

    void on_noticeBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::first_window_for_visitor *ui;
    detailoperation_for_visitor *dtv;
    readnotice *rn;
    registerwindow *rw;
    USEROperator USER;
    QPropertyAnimation *m_propertyAnimation;
    QPropertyAnimation *m_propertyAnimation2;
    bool m_bSideflag;
};

#endif // FIRST_WINDOW_FOR_VISITOR_H
