#include "forget_questioncheck.h"
#include "ui_forget_questioncheck.h"
#include "USEROperator.h"
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include "forgetpassword.h"

forget_questioncheck::forget_questioncheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forget_questioncheck)
{
    ui->setupUi(this);
    setWindowTitle("验证密保信息");
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
    ui->apply->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:black;"//设置按钮字体颜色
                         "font-size:9px;"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "color:red;"
                         "font-size:11px;"
                         "}");
    ui->apply->setCursor(QCursor(Qt::PointingHandCursor));
    USER.USEROpen();
}

forget_questioncheck::~forget_questioncheck()
{
    delete ui;
}

void forget_questioncheck::showOP()
{
    ui->showquestion->setReadOnly(true);
    ui->showquestion->setEnabled(false);
    ui->showquestion->setText(_question);
    if(_question != "" && _email == "")
    {
        ui->inputemail->setReadOnly(true);
        ui->inputemail->setEnabled(false);
        ui->inputemail->setText("您暂未绑定邮箱");
        ui->answerquestion->setPlaceholderText("(请输入密保答案)");
    }
    if(_question == "" && _email != "")
    {
        ui->showquestion->setText("您暂未设置密保问题");
        ui->answerquestion->setReadOnly(true);
        ui->answerquestion->setEnabled(false);
        ui->answerquestion->setText("");
        ui->inputemail->setPlaceholderText("(请输入邮箱)");
    }
}

void forget_questioncheck::on_check_clicked()
{
    bool Ischeck = false;
    QString nanswer = ui->answerquestion->text();
    QString nemail = ui->inputemail->text();
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 密保答案, 邮箱 FROM register where account = '"+account+"'");
    while(query.next())
    {
        QString realanswer = query.value(0).toString();
        QString realemail = query.value(1).toString();
        if(realanswer == nanswer && realemail == nemail)
            Ischeck = true;
    }
    if(Ischeck)
    {
        fp = new forgetpassword;
        fp->account = account;
        fp->showOP();
        fp->show();
        close();
    }
    else
        QMessageBox::warning(this, "警告", "密保答案或邮箱输入错误！");
}


void forget_questioncheck::on_cancel_clicked()
{
    close();
}


void forget_questioncheck::on_apply_clicked()
{
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 学号, 姓名, 密保问题 FROM register where account = '"+account+"'");
    query.first();
    QString naccount = account;
    QString nschoolnum = query.value(0).toString();
    QString nname = query.value(1).toString();
    QString nquestion = query.value(2).toString();
    fpa = new forgetpasswordapply;
    fpa->account = naccount;
    fpa->name = nname;
    fpa->schoolnum = nschoolnum;
    fpa->_question = nquestion;
    fpa->showOP();
    fpa->show();
    close();
}


