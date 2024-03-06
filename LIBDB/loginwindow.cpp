#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>
#include <QMessageBox>

loginwindow::loginwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwindow)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    setGeometry(600, 100, 450, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG.png"));
    ui->inputaccount->setFocus();
    ui->loginorder->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#bd5d5d;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#bd5d5d;"
                         "color:red;"
                         "}");
    ui->loginorder->setCursor(QCursor(Qt::PointingHandCursor));
    ui->exitBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#bd5d5d;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#bd5d5d;"
                         "color:red;"
                         "}");
    ui->exitBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->forgetBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#bd5d5d;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#bd5d5d;"
                         "color:red;"
                         "}");
    ui->forgetBtn->setCursor(QCursor(Qt::PointingHandCursor));
    USER.USEROpen();
    ui->inputaccount->setPlaceholderText("(请输入账号)");
    ui->inputpassword->setPlaceholderText("(请输入密码)");
    ui->inputpassword->setEchoMode(QLineEdit::Password);
}

loginwindow::~loginwindow()
{
    delete ui;
}

void loginwindow::on_loginorder_clicked()
{
    bool login = false;
    bool Isaccount = false;
    QString naccount = ui->inputaccount->text();
    QString npassword = ui->inputpassword->text();
    QSqlQuery query(USER.dbcon);
    query.prepare("SELECT account,password,identification,状态,校区 FROM register");
    query.exec();
    while (query.next())
    {
        QString realaccount = query.value("account").toString();
        QString realpassword = query.value("password").toString();
        QString narea = query.value("校区").toString();
        QString id = query.value("identification").toString();
        QString state = query.value(3).toString();
        if(realaccount==naccount) Isaccount = true;
        if(realaccount==naccount&&realpassword==npassword&&id=="user"&&state=="unlocked")
        {
            login = true;
            query.exec("UPDATE register SET count = 0 WHERE account = '"+naccount+"'");
            fu = new first_window_for_user;
            fu->account = naccount;    //读取账号，借书还书都要利用这个记录
            fu->area = narea;
            fu->dt->account = naccount;
            fu->setQLable();
            fu->checkcredit();
            close();
        }
        else if(realaccount==naccount&&realpassword==npassword&&id=="Administrator"&&state=="unlocked")
        {
            login = true;
            query.exec("UPDATE register SET count = 0 WHERE account = '"+naccount+"'");
            fa = new first_window_for_Administrator;
            fa->account = naccount;    //读取账号，借书还书都要利用这个记录
            fa->setQLable();
            fa->show();
            close();
        }
    }
    if(naccount == "")
        QMessageBox::warning(this, "警告", "请输入您的帐号！");
    else if(!Isaccount)
        QMessageBox::warning(this, "警告", "该账号不存在！");
    else if(!login)
    {

        query.exec("UPDATE register SET count = count + 1 WHERE account = '"+naccount+"'");
        query.exec("SELECT count, 状态 FROM register WHERE account = '"+naccount+"'");
        query.first();
        if(query.value(1).toString() == "locked")
        {
            QMessageBox::warning(this, "警告", "(由于借书未还、登录次数超出限制等)该账号已锁定！");
            query.exec("UPDATE register SET count = count - 1 WHERE account = '"+naccount+"'");
        }
        else if(query.value(1).toString() == "approving")
        {
            QMessageBox::warning(this, "警告", "该账号正在审批中！\n请等待管理员审核！");
            query.exec("UPDATE register SET count = count - 1 WHERE account = '"+naccount+"'");
        }
        else if(query.value(0).toInt() >= 3)
        {
            query.exec("UPDATE register SET 状态 = 'locked' WHERE account = '"+naccount+"'");
            QMessageBox::StandardButton result = QMessageBox::question(this,"警告","已3次输入密码错误！\n  账号已被锁定!\n  是否忘记密码？");
            if(result == QMessageBox::Yes)
            {
                fpc = new forgetpasswordcheck;
                fpc->account = naccount;
                fpc->showOP();
                fpc->show();
                close();
            }
        }
        else
        {
            int rest = 3 - query.value(0).toInt();
            int ncount = query.value(0).toInt();
            QMessageBox::warning(this,"错误",tr("账号或密码已输入错误%1次！\n        还剩%2次机会!").arg(ncount).arg(rest));
        }
    }
}


void loginwindow::on_forgetBtn_clicked()
{
    bool Isaccount = false;
    QString naccount = ui->inputaccount->text();
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT account FROM register");
    while (query.next())
    {
        QString realaccount = query.value(0).toString();
        if(realaccount==naccount) Isaccount = true;
    }
    query.exec("SELECT 状态 FROM register WHERE account = '"+naccount+"'");
    query.first();
    QString state = query.value(0).toString();
    if(naccount == "")
    {
        fpc = new forgetpasswordcheck;
        fpc->account = naccount;
        fpc->show();
        close();
    }
    else if(!Isaccount)
        QMessageBox::warning(this, "警告", "该账号不存在！");
    else
    {
        fpc = new forgetpasswordcheck;
        fpc->account = naccount;
        fpc->showOP();
        fpc->show();
        close();
    }
}


void loginwindow::on_exitBtn_clicked()
{
    close();
}
