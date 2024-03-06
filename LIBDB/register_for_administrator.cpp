#include "register_for_administrator.h"
#include "qbuttongroup.h"
#include "ui_register_for_administrator.h"

register_for_administrator::register_for_administrator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_for_administrator)
{
    ui->setupUi(this);
    setWindowTitle("管理员注册");
    setGeometry(600, 100, 450, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG.png"));
    ui->registerorder->setStyleSheet(   //正常状态样式
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
    ui->registerorder->setCursor(QCursor(Qt::PointingHandCursor));
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
    ui->student->setStyleSheet(   //正常状态样式
                                  "QRadioButton{"
                                  "border-radius:10px;"//设置圆角半径
                                  "color:white;"//设置按钮字体颜色
                                  "}"
                                  //鼠标悬停样式
                                  "QRadioButton:hover{"
                                  "color:red;"
                                  "}");
    ui->student->setCursor(QCursor(Qt::PointingHandCursor));
    ui->teacher->setStyleSheet(   //正常状态样式
                                  "QRadioButton{"
                                  "border-radius:10px;"//设置圆角半径
                                  "color:white;"//设置按钮字体颜色
                                  "}"
                                  //鼠标悬停样式
                                  "QRadioButton:hover{"
                                  "color:red;"
                                  "}");
    ui->teacher->setCursor(QCursor(Qt::PointingHandCursor));
    QButtonGroup *bg = new QButtonGroup;
    bg->addButton(ui->student,0);
    bg->addButton(ui->teacher,1);
    ui->student->setAutoExclusive(true);
    ui->teacher->setAutoExclusive(true);
    USER.USEROpen();
    ui->inputpassword->setEchoMode(QLineEdit::Password);
    ui->sureinputpassword->setEchoMode(QLineEdit::Password);
}

register_for_administrator::~register_for_administrator()
{
    delete ui;
}

void register_for_administrator::settext()
{
    ui->inputaccount->setText(account);
    ui->inputpassword->setText(password);
}

void register_for_administrator::on_registerorder_clicked()
{
    QString newaccount = ui->inputaccount->text();
    QString newpassword = ui->inputpassword->text();
    QString surepassword = ui->sureinputpassword->text();
    QString newname = ui->inputname->text();
    QString newnum = ui->inputnum->text();
    QString newmail = ui->inputmail->text();
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT account FROM register");
    bool ok = true;
    bool ok2 = false;
    bool ok3 = false;
    bool ok4 = true;
    if(newpassword == surepassword)
    {
    while(query.next())
    {
        if(query.value(0).toString()==newaccount)
        {
           ok=false;
        }
    }
    query.exec("SELECT keyword FROM key");
    while(query.next())
    {
        if(query.value(0).toString()==ui->inputketword->text())
        {
           ok3=true;
        }
    }
    query.exec("SELECT 账号 FROM admini_apply");
    while(query.next())
    {
        if(query.value(0).toString()==ui->inputaccount->text())
        {
           ok4=false;
        }
    }
    if(ui->student->isChecked()||ui->teacher->isChecked())
    {
        ok2=true;
    }
    if(ok&&ok2&&ok3&&ok4)
    {
        if(newaccount==""||newpassword==""||newname==""||newnum=="")
        {
            QMessageBox::warning(this,"错误","请完善个人信息！");
        }
        else
        {
            QString character;
            if(ui->student->isChecked())
            {
                character = "学生";
                query.prepare("insert into admini_apply (账号,密码,姓名,学号,邮箱,身份) values ("+newaccount+" , '"+newpassword+"',  '"+newname+"', '"+newnum+"', '"+newmail+"','"+character+"');");
                query.exec();
            }
            if(ui->teacher->isChecked())
            {
                character = "教师";
                query.prepare("insert into admini_apply (账号,密码,姓名,学号,邮箱,身份) values ("+newaccount+" , '"+newpassword+"',  '"+newname+"', '"+newnum+"', '"+newmail+"','"+character+"');");
                query.exec();
            }
            QMessageBox::warning(this,"提示","注册成功！等待审核！");
            close();
        }
    }
    else if(ok==false)
    {
        QMessageBox::warning(this,"错误","该账号已存在！");
    }
    else if(ok==true&&ok2==false&&ok3==true&&ok4==true)
    {
        QMessageBox::warning(this,"错误","请完善个人信息！");
    }
    else if(ok3==false)
    {
        QMessageBox::warning(this,"错误","请输入正确的密钥！");
    }
    else if(ok4==false)
    {
        QMessageBox::warning(this,"错误","请不要重复申请！");
    }
    }
    else
    {
        QMessageBox::warning(this,"错误","请检查您的密码！");
    }
}


void register_for_administrator::on_pushButton_clicked()
{
    close();
}


void register_for_administrator::on_exitBtn_clicked()
{
    close();
}

