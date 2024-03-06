#include "forgetpasswordapply.h"
#include "ui_forgetpasswordapply.h"
#include <QSqlQuery>
#include <QMessageBox>

forgetpasswordapply::forgetpasswordapply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpasswordapply)
{
    ui->setupUi(this);
    setWindowTitle("申诉");
    setGeometry(300, 100, 1000, 618);
    ui->submit->setDefault(1);
    ui->submit->setStyleSheet(   //正常状态样式
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
    ui->submit->setCursor(QCursor(Qt::PointingHandCursor));
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
    QStringList cbList;
    cbList << "忘记密码" << "账户锁定";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("忘记密码");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    ui->registerdate->setPlaceholderText("(年/月/日)");
    USER.USEROpen();
}

forgetpasswordapply::~forgetpasswordapply()
{
    delete ui;
}

void forgetpasswordapply::showOP()
{
    ui->showaccount->setReadOnly(true);
    ui->showaccount->setEnabled(false);
    ui->showaccount->setText(account);
    ui->showschoolnum->setReadOnly(true);
    ui->showschoolnum->setEnabled(false);
    ui->showschoolnum->setText(schoolnum);
    ui->showname->setReadOnly(true);
    ui->showname->setEnabled(false);
    ui->showname->setText(name);
    ui->showquestion->setText(_question);
}

void forgetpasswordapply::on_submit_clicked()
{
    QString naccount = ui->showaccount->text();
    QString nrequest = ui->depcbBox->currentText().trimmed();
    QString nname = ui->showname->text();
    QString nschoolnum = ui->showschoolnum->text();
    QString nemail = ui->inputemail->text();
    QString nquestion = ui->showquestion->text();
    QString nanswer = ui->answerquestion->text();
    QString ndate = ui->registerdate->text();
    QSqlQuery query(USER.dbcon);
    query.exec("insert into request (账号,请求,姓名,学号,邮箱,密保问题,密保答案,注册日期) values ("+naccount+" , '"+nrequest+"', '"+nname+"' , '"+nschoolnum+"', '"+nemail+"', '"+nquestion+"', '"+nanswer+"', '"+ndate+"');");
    query.exec("UPDATE register SET 状态 = 'approving' WHERE account = '"+account+"'");
    if(nrequest == "忘记密码")
        QMessageBox::warning(this, "提示", "忘记密码申诉成功,待管理员审批过后初始密码设为123456！");
    else
        QMessageBox::warning(this, "提示", "申诉成功,请待管理员审批！");
    close();
}


void forgetpasswordapply::on_cancel_clicked()
{
    close();
}
