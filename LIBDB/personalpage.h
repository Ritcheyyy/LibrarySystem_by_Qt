#ifndef PERSONALPAGE_H
#define PERSONALPAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QLineEdit>
#include "USEROperator.h"


namespace Ui {
class personalpage;
}

class personalpage : public QWidget
{
    Q_OBJECT

public:
    explicit personalpage(QWidget *parent = nullptr);
    ~personalpage();
    QString account;
    QString password;
    void personalpageOP();
    void edit();
private slots:

    void on_editBtn_clicked();

    void on_ok_clicked();

    void on_editmail_clicked();

    void on_editquestion_clicked();

private:
    Ui::personalpage *ui;
    USEROperator USER;
    QLineEdit *input;
    int click;
};

#endif // PERSONALPAGE_H
