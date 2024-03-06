#include "setmail.h"
#include "ui_setmail.h"

setmail::setmail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setmail)
{
    ui->setupUi(this);
    setWindowTitle("绑定邮箱");
    setGeometry(600, 250, 400, 300);
    ui->cancel->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#67a6f8;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#5f9ae6;"
                         "color:red;"
                         "}");
    ui->ok->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#67a6f8;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#5f9ae6;"
                         "color:red;"
                         "}");
    USER.USEROpen();
}

setmail::~setmail()
{
    delete ui;
}

void setmail::on_cancel_clicked()
{
    close();
}


void setmail::on_ok_clicked()
{
    QSqlQuery query(USER.dbcon);
    QString mail = ui->inputmail->text();
    if(mail!="")
    {
        query.exec("UPDATE register SET 邮箱 = '"+mail+"' WHERE account = '"+account+"'");
        QMessageBox::warning(this,"提示","修改成功，请重新登录！");
        close();
    }
    else
    {
        QMessageBox::warning(this,"警告","邮箱不能为空！");
    }
}

