#ifndef REGISTER_FOR_ADMINISTRATOR_H
#define REGISTER_FOR_ADMINISTRATOR_H

#include <QDialog>
#include <QButtonGroup>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class register_for_administrator;
}

class register_for_administrator : public QDialog
{
    Q_OBJECT

public:
    explicit register_for_administrator(QWidget *parent = nullptr);
    ~register_for_administrator();
    QString account;
    QString password;
    void settext();

private slots:
    void on_registerorder_clicked();

    void on_pushButton_clicked();

    void on_exitBtn_clicked();

private:
    Ui::register_for_administrator *ui;
    USEROperator USER;
};

#endif // REGISTER_FOR_ADMINISTRATOR_H
