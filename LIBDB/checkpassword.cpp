#include "checkpassword.h"
#include "ui_checkpassword.h"

checkpassword::checkpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkpassword)
{
    ui->setupUi(this);
    setWindowTitle("验证");
    setGeometry(600, 250, 400, 300);
    ui->cancelBtn->setStyleSheet(   //正常状态样式
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
    ui->cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->ok->setStyleSheet(   //正常状态样式
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
    ui->ok->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &checkpassword::close);
    USER.USEROpen();
    pp = NULL;
    flag = 0;
}

checkpassword::~checkpassword()
{
    delete ui;
}

void checkpassword::on_ok_clicked()
{
    QString p = ui->lineEdit->text();
    if(p!="")
    {
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT password FROM register WHERE account = '"+account+"'");
    query.first();
    if(p!=query.value(0).toString())
    {
        flag = 0;
        query.exec("UPDATE register SET count = count+1 WHERE account = '"+account+"'");
        query.exec("SELECT count FROM register WHERE account = '"+account+"'");
        query.first();
        if(query.value(0).toInt() >= 3)
        {
            query.exec("UPDATE register SET 状态 = 'locked' WHERE account = '"+account+"'");
            QMessageBox::StandardButton result = QMessageBox::information(this,"警告","已3次输入密码错误！\n  账号已被锁定!");
            if(result == QMessageBox::Yes)
            {
                delete this;
                delete pp;
            }
        }
        else
            QMessageBox::warning(this,"错误","您的密码有误！");
    }
    else
    {
    query.exec("UPDATE register SET count = 0 WHERE account = '"+account+"'");
    if(flag == 1)
    {
        QString thepassword = ui->lineEdit->text();
        pp->password = thepassword;
        pp->edit();
        close();
    }
    else if(flag==2)
    {
        sq = new setquestion;
        sq->account = account;
        sq->show();
        close();
    }
    else if(flag==3)
    {
        sm = new setmail;
        sm->account = account;
        sm->show();
        close();
    }
    else if(flag==0)
    {
        close();
    }
    }
    }
    else
    {
        QMessageBox::warning(this,"警告","密码不能为空！");
    }
}

