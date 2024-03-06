#ifndef DEALAPPLY_H
#define DEALAPPLY_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include "USEROperator.h"

namespace Ui {
class dealapply;
}

class dealapply : public QWidget
{
    Q_OBJECT

public:
    explicit dealapply(QWidget *parent = nullptr);
    ~dealapply();
    void dealapplyOP();

private slots:
    void on_deleteBtn_clicked();

private:
    Ui::dealapply *ui;
    QSqlTableModel *tm;
    USEROperator USER;
};

#endif // DEALAPPLY_H
