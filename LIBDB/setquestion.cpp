#include "setquestion.h"
#include "ui_setquestion.h"

setquestion::setquestion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setquestion)
{
    ui->setupUi(this);
    setWindowTitle("修改密保");
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

setquestion::~setquestion()
{
    delete ui;
}

void setquestion::on_ok_clicked()
{
    QSqlQuery query(USER.dbcon);
    QString question = ui->inputquestion->text();
    QString answer = ui->inputanswer->text();
    query.exec("UPDATE register SET 密保问题 = '"+question+"' WHERE account = '"+account+"'");
    query.exec("UPDATE register SET 密保答案 = '"+answer+"' WHERE account = '"+account+"'");
    QMessageBox::warning(this,"提示","修改成功，请重新登录！");
    close();
}


void setquestion::on_cancel_clicked()
{
    close();
}

