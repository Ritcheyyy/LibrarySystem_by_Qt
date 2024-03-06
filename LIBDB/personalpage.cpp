#include <QPushButton>
#include <QMessageBox>
#include "personalpage.h"
#include "checkpassword.h"
#include "ui_personalpage.h"

personalpage::personalpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personalpage)
{
    ui->setupUi(this);
    setWindowTitle("个人主页");
    setGeometry(600, 100, 400, 600);
    ui->editBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#67a6f8;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#679af8;"
                         "color:red;"
                         "}");
    ui->editBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->ok->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#77a677;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#779a77;"
                         "color:red;"
                         "}");
    ui->ok->setCursor(QCursor(Qt::PointingHandCursor));
    ui->editquestion->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#99a600;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#999a00;"
                         "color:red;"
                         "}");
    ui->editquestion->setCursor(QCursor(Qt::PointingHandCursor));
    ui->editmail->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#88a688;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#889a88;"
                         "color:red;"
                         "}");
    ui->editmail->setCursor(QCursor(Qt::PointingHandCursor));
    ui->laccount->setReadOnly(true);
    ui->laccount->setEnabled(false);
    ui->lname->setReadOnly(true);
    ui->lname->setEnabled(false);
    ui->lquestion->setReadOnly(true);
    ui->lquestion->setEnabled(false);
    ui->lcredit->setReadOnly(true);
    ui->lcredit->setEnabled(false);
    ui->lnum->setReadOnly(true);
    ui->lnum->setEnabled(false);
    ui->lmail->setReadOnly(true);
    ui->lmail->setEnabled(false);
    ui->lwork->setReadOnly(true);
    ui->lwork->setEnabled(false);
    USER.USEROpen();
    personalpageOP();
    password = "";
    click = 0;

}

personalpage::~personalpage()
{
    delete ui;
}

void personalpage::personalpageOP()
{
    QSqlQuery query(USER.dbcon);
    query.prepare("SELECT account,学号,姓名,密保问题,邮箱,信用,职务 FROM register WHERE account = '"+account+"'");
    query.exec();
    query.first();
    QString num = query.value("学号").toString();
    QString name = query.value("姓名").toString();
    QString question = query.value("密保问题").toString();
    QString mail = query.value("邮箱").toString();
    QString credit = query.value("信用").toString();
    QString work = query.value("职务").toString();
    ui->laccount->setText(account);
    ui->lcredit->setText(credit);
    ui->lnum->setText(num);
    ui->lname->setText(name);
    ui->lwork->setText(work);
    if(question=="")
        ui->lquestion->setText("否");
    else
        ui->lquestion->setText("是");
    ui->lmail->setText(mail);
}


void personalpage::on_editBtn_clicked()
{
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 状态 FROM register where account = '"+account+"'");
    query.first();
    if(query.value(0).toString() == "locked")
        QMessageBox::warning(this,"错误","您的账户已被锁定！\n 无法修改个人信息！");
    else if(password==""&&click==0)
    {
        checkpassword *ck = new checkpassword;
        ck->pp = this;
        ck->flag=1;
        ck->account = account;
        ck->show();
        click++;
    }
}

void personalpage::on_ok_clicked()
{
    click = 0;
    password = "";
    ui->laccount->setReadOnly(true);
    ui->laccount->setEnabled(false);
    ui->lname->setReadOnly(true);
    ui->lname->setEnabled(false);
    ui->lnum->setReadOnly(true);
    ui->lnum->setEnabled(false);
    ui->lwork->setReadOnly(true);
    ui->lwork->setEnabled(false);
    QString name = ui->lname->text();
    QString num = ui->lnum->text();
    QString newaccount = ui->laccount->text();
    QString newwork = ui->lwork->text();
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 姓名,学号,邮箱,职务 FROM register WHERE account = '"+account+"'");
    query.first();
    QString myname = query.value("姓名").toString();
    QString mynum = query.value("学号").toString();
    QString mymail = query.value("邮箱").toString();
    QString mywork = query.value("职务").toString();
    bool ok = true;
    query.exec("SELECT account,姓名,学号 FROM register");
    while(query.next())
    {
        if(query.value("account").toString()==newaccount)
        {
            if(newaccount!=account)
            {
                ok = false;
                ui->laccount->setText(account);
                ui->lname->setText(myname);
                ui->lnum->setText(mynum);
                QMessageBox::warning(this,"提示","无效修改(已存在的用户信息、未作修改等)！");
                break;
            }
        }
    }
    if(ok)
    {
        query.prepare("UPDATE register SET account = '"+newaccount+"' WHERE account='"+account+"'");
        query.exec();
        account = newaccount;
        query.prepare("UPDATE register SET 姓名 = '"+name+"' WHERE account='"+account+"'");
        query.exec();
        query.prepare("UPDATE register SET 学号 = '"+num+"' WHERE account='"+account+"'");
        query.exec();
        query.prepare("UPDATE register SET 职务 = '"+newwork+"' WHERE account='"+account+"'");
        query.exec();
        QMessageBox::warning(this,"提示","修改成功，请重新登录！");
    }
}

void personalpage::edit()
{
    QSqlQuery query(USER.dbcon);
    query.prepare("SELECT password FROM register WHERE account = '"+account+"'");
    query.exec();
    query.first();
    QString realpassword = query.value("password").toString();
    if(password==realpassword)
    {
        ui->lwork->setReadOnly(false);
        ui->lwork->setEnabled(true);
        ui->lname->setReadOnly(false);
        ui->lname->setEnabled(true);
        ui->lnum->setReadOnly(false);
        ui->lnum->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this,"错误","密码错误！");
    }
}


void personalpage::on_editmail_clicked()
{
    checkpassword *ck = new checkpassword;
    ck->pp = this;
    ck->flag=3;
    ck->account = account;
    ck->show();
}


void personalpage::on_editquestion_clicked()
{
    checkpassword *ck = new checkpassword;
    ck->pp = this;
    ck->flag=2;
    ck->account = account;
    ck->show();
}

