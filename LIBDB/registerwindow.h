#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "USEROperator.h"
#include "register_for_administrator.h"
#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <string>
#include <QButtonGroup>
#include <QtSql/QSqlTableModel>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class registerwindow;
}
QT_END_NAMESPACE


class registerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit registerwindow(QWidget *parent = nullptr);
    ~registerwindow();
    void registerOP();

private slots:
    void on_registerorder_clicked();

    void on_registerorder_2_clicked();

    void on_exitBtn_clicked();

private:
    Ui::registerwindow *ui;
    QSqlTableModel *account;
    QSqlTableModel *password;
    register_for_administrator *ra;
    USEROperator USER;
};

#endif // REGISTERWINDOW_H
