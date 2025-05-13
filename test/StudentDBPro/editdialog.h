#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QtSql/QSqlRecord>

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr, QSqlRecord *recp=nullptr);
    ~EditDialog();

private slots:
    void on_updateBtn_clicked();

private:
    Ui::EditDialog *ui;
    QSqlRecord *editRec;
};

#endif // EDITDIALOG_H
