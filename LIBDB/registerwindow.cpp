#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "USEROperator.h"
#include <QString>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>

using namespace std;

registerwindow::registerwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerwindow)
{
    ui->setupUi(this);
    setWindowTitle("注册界面");
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
    ui->registerorder_2->setStyleSheet(   //正常状态样式
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
    ui->registerorder_2->setCursor(QCursor(Qt::PointingHandCursor));
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
    QStringList cbList;
    cbList << "南校区" << "北校区" << "东校区" << "珠海校区" << "深圳校区";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("南校区");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
    ui->inputpassword->setEchoMode(QLineEdit::Password);
    ui->sureinputpassword->setEchoMode(QLineEdit::Password);
}

registerwindow::~registerwindow()
{
    delete ui;
}

void registerwindow::on_registerorder_clicked()
{
    QString newaccount = ui->inputaccount->text();
    QString newpassword = ui->inputpassword->text();
    QString surepassword = ui->sureinputpassword->text();
    QString newname = ui->inputname->text();
    QString newnum = ui->inputnum->text();
    QString area = ui->depcbBox->currentText().trimmed();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM");
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT account FROM register");
    bool ok = true;
    bool ok2 = false;
    if(newpassword == surepassword)
    {
    while(query.next())
    {
        if(query.value(0).toString()==newaccount)
        {
           ok=false;
        }
    }
    if(ui->student->isChecked()||ui->teacher->isChecked())
    {
        ok2=true;
    }
    if(ok&&ok2)
    {
        if(newaccount==""||newpassword==""||newname==""||newnum=="")
        {
            QMessageBox::warning(this,"错误","请完善个人信息！");
        }
        else
        {
            QString id = "user";
            QString character;
            if(ui->student->isChecked())
            {
                character = "学生";
                query.prepare("insert into register (account,password,identification,身份,学号,姓名,信用,状态,注册时间,校区,当前借书) values ('"+newaccount+"' , '"+newpassword+"', '"+id+"' , '"+character+"', '"+newnum+"', '"+newname+"','良好','unlocked','"+time+"','"+area+"',0);");
            }
            if(ui->teacher->isChecked())
            {
                character = "教师";
                query.prepare("insert into register (account,password,identification,身份,学号,姓名,信用,状态,注册时间,校区,当前借书) values ('"+newaccount+"' , '"+newpassword+"', '"+id+"' , '"+character+"', '"+newnum+"', '"+newname+"','良好','unlocked','"+time+"','"+area+"',0);");
            }
            if(query.exec()) QMessageBox::warning(this,"提示","注册成功！");
            else QMessageBox::warning(this,"提示","注册失败！");
            close();
        }
    }
    else if(ok==false)
    {
        QMessageBox::warning(this,"错误","该账号已存在！");
    }
    else if(ok==true&&ok2==false)
    {
        QMessageBox::warning(this,"错误","请完善个人信息！");
    }
    }
    else
    {
        QMessageBox::warning(this,"错误","请检查您的密码！");
    }
}
void registerwindow::registerOP()
{
    QSqlRecord record = account->record();  // 获取空记录
    int row = account->rowCount();          // 获取行号
    account->insertRecord(row, record);
}

void registerwindow::on_registerorder_2_clicked()
{
    ra = new register_for_administrator;
    ra->account = ui->inputaccount->text();
    ra->password = ui->inputpassword->text();
    ra->settext();
    ra->show();
    close();
}


void registerwindow::on_exitBtn_clicked()
{
    close();
}
