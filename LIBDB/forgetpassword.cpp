#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "USEROperator.h"
#include <QMessageBox>
#include <QSqlQuery>

forgetpassword::forgetpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
    setWindowTitle("修改密码");
    setGeometry(600, 250, 450, 300);
    ui->OK->setDefault(1);
    ui->OK->setStyleSheet(   //正常状态样式
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
    ui->OK->setCursor(QCursor(Qt::PointingHandCursor));
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
    ui->cancel->setCursor(QCursor(Qt::PointingHandCursor));
    USER.USEROpen();
    ui->newpassword->setEchoMode(QLineEdit::Password);
    ui->checkpassword->setEchoMode(QLineEdit::Password);
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

void forgetpassword::showOP()
{
    ui->showaccount->setReadOnly(true);
    ui->showaccount->setEnabled(false);
    ui->showaccount->setText(account);
}

void forgetpassword::on_OK_clicked()
{
    QString newpassword = ui->newpassword->text();
    QString checkpassword = ui->checkpassword->text();
    if(checkpassword != newpassword && newpassword != "" && checkpassword != "")
        QMessageBox::warning(this, "警告", "两次输入的密码不一致！\n   请重新输入！");
    else if(newpassword == "")
    {
        QMessageBox::warning(this, "警告", "请输入您的新密码！");
    }
    else if(checkpassword == "" && newpassword != "")
    {
        QMessageBox::warning(this, "警告", "请确认您的新密码！");
    }
    else
    {
        QSqlQuery query(USER.dbcon);
        query.exec("UPDATE register SET password = '"+newpassword+"' WHERE account = '"+account+"'");
        query.prepare("UPDATE register SET count = 0 WHERE account = '"+account+"'");
        if(query.exec())
        {
            QMessageBox::warning(this, "提示", "密码修改成功！");
            close();
        }
    }
}


void forgetpassword::on_cancel_clicked()
{
    close();
}

