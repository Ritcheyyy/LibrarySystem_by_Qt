#include "advice_for_library.h"
#include "ui_advice_for_library.h"

advice_for_library::advice_for_library(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::advice_for_library)
{
    ui->setupUi(this);
    setWindowTitle("图书馆信箱");
    setGeometry(600, 100, 400, 600);
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
    connect(ui->cancel, &QPushButton::clicked, this, &advice_for_library::close); // 信号槽
    USER.USEROpen();
}

advice_for_library::~advice_for_library()
{
    delete ui;
}

void advice_for_library::on_submit_clicked()
{
    QSqlQuery query(USER.dbcon);
    QString advice = ui->textEdit->toPlainText();
    if(advice!="")
    {
        query.exec("insert into advice (账号,建议) values ("+account+" , '"+advice+"');");
        QMessageBox::warning(this,"提交成功","感谢您的宝贵建议！");
        close();
    }
    else
    {
        QMessageBox::warning(this,"警告","请输入您的建议！");
    }
}

