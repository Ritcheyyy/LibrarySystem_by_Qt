#include "forgetpasswordcheck.h"
#include "ui_forgetpasswordcheck.h"
#include "USEROperator.h"
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include "forget_questioncheck.h"

forgetpasswordcheck::forgetpasswordcheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpasswordcheck)
{
    ui->setupUi(this);
    setWindowTitle("验证信息");
    setGeometry(600, 250, 450, 300);
    ui->check->setDefault(1);
    ui->check->setStyleSheet(   //正常状态样式
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
    ui->check->setCursor(QCursor(Qt::PointingHandCursor));
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
}

forgetpasswordcheck::~forgetpasswordcheck()
{
    delete ui;
}

void forgetpasswordcheck::showOP()
{
    ui->showaccount->setReadOnly(true);
    ui->showaccount->setEnabled(false);
    ui->showaccount->setText(account);
}

void forgetpasswordcheck::on_check_clicked()
{
    bool Ischeck = false;
    QString naccount = ui->showaccount->text();
    QString nschoolnum = ui->inputschoolnum->text();
    QString nusername = ui->inputusername->text();
    if(naccount == "")
        QMessageBox::warning(this, "警告", "请输入您的账号！");
    else
    {
        QSqlQuery query(USER.dbcon);
        query.exec("SELECT 学号,姓名,邮箱 FROM register where account = '"+naccount+"'");
        while(query.next())
        {
            QString realschoolnum = query.value(0).toString();
            QString realusername = query.value(1).toString();
            if(realschoolnum == nschoolnum && realusername == nusername)
                Ischeck = true;
        }
        if(Ischeck)
        {
            query.exec("SELECT 邮箱, 密保问题 FROM register where account = '"+naccount+"'");
            query.first();
            QString kemail = query.value(0).toString();
            QString kquestion = query.value(1).toString();
            //qDebug() << query.value(0).toString();
            if(kquestion == "" && kemail == "")
            {
                fp = new forgetpassword;
                fp->account = naccount;
                fp->showOP();
                fp->show();
                close();
            }
            else
            {
                fqc = new forget_questioncheck;
                fqc->account = ui->showaccount->text();
                fqc->_email = kemail;
                fqc->_question = kquestion;
                //qDebug() << fqc->_question;
                fqc->showOP();
                fqc->show();
                close();
            }
        }
        else
            QMessageBox::warning(this, "警告", "验证信息输入错误！");
    }
}


void forgetpasswordcheck::on_cancel_clicked()
{
    close();
}

