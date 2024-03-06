#include "first_window_for_user.h"
#include "ui_first_window_for_user.h"
#include <QPainter>

first_window_for_user::first_window_for_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::first_window_for_user)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统个人用户端");
    setGeometry(200, 100, 1200, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG3.jpg"));
    connect(ui->exitBtn, &QPushButton::clicked, this, &first_window_for_user::close); // 信号槽
    ui->detailBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                                    "font: 700 15pt '等线';"
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                                    "font: 700 15pt '等线';"
                         "color:red;"
                         "}");
    ui->detailBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->exitBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:6px;"//设置圆角半径
                                  "font: 700 15pt '等线';"
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:10px;"//设置圆角半径
                                  "font: 700 15pt '等线';"
                         "color:red;"
                         "}");
    ui->exitBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->noticeBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                                    "font: 700 15pt '等线';"
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                                    "font: 700 15pt '等线';"
                         "color:red;"
                         "}");
    ui->noticeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->setBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                 "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "color:red;"
                         "}");
    ui->setBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->adviceBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                    "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->adviceBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->borrowBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                    "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->borrowBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->myreserveBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                    "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->myreserveBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->reserveBtn->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                     "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                                     "font: 700 15pt '等线';"
                         "color:red;"
                         "}");
    ui->pushButton->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:transparent;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                                     "font: 700 15pt '等线';"
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->reserveBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    USER.USEROpen();
    ui->sidewidget->move(-ui->sidewidget->width(),0);// 左侧停靠
    ui->pushButton->move(-1,ui->sidewidget->height()/10);
    m_propertyAnimation = new QPropertyAnimation(ui->sidewidget,"geometry");
    m_propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint);
    m_propertyAnimation->setDuration(300);
    m_propertyAnimation2 = new QPropertyAnimation(ui->pushButton,"geometry");
    m_propertyAnimation2->setEasingCurve(QEasingCurve::InOutQuint);
    m_propertyAnimation2->setDuration(200);
    m_bSideflag = false;
    pp = new personalpage;
    rn = new readnotice;
    al = new advice_for_library;
    ro = new reserveoperation;
    rb = new returnbook;
    dt = new detailoperation;
    dr = new deletereserve;
    ui->stackedWidget->addWidget(rn);
    ui->stackedWidget->addWidget(ro);
    ui->stackedWidget->addWidget(al);
    ui->stackedWidget->addWidget(pp);
    ui->stackedWidget->addWidget(rb);
    ui->stackedWidget->addWidget(dt);
    ui->stackedWidget->addWidget(dr);
}

first_window_for_user::~first_window_for_user()
{
    delete ui;
}

void first_window_for_user::setQLable()
{
    QString str;
    QSqlQuery query3(USER.dbcon);
    query3.exec("SELECT 身份,姓名 FROM register WHERE account = '"+account+"'");
    query3.first();
    QString name = query3.value("姓名").toString();
    QString id = query3.value("身份").toString();
    if(id=="学生")
        str = "欢迎"+name+"同学";
    else
        str = "欢迎"+name+"老师";
    ui->header->setStyleSheet("QLabel{"
                              "background-color:transparent;"//设置按钮背景色
                              "border-radius:10px;"//设置圆角半径
                              "font: 700 15pt '等线';"
                              "color:white;"//设置按钮字体颜色
                              "}");
    ui->header->setProperty("text",str);
    show();
    QSqlQuery query(USER.dbcon);
    QSqlQuery query2(USER.dbcon);
    QSqlQuery query4(USER.dbcon);
    query.exec("SELECT 借书时间,bookname FROM borrow_record WHERE account = '"+account+"'");
    QString time1,time2,returntime2,nbookname;
    QDateTime d1,d2;
    bool goodcredit = true;
    while(query.next())
    {
        time1 = query.value(0).toString();
        time2 = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        d1 = QDateTime::fromString(time1,"yyyy-MM-dd hh:mm:ss");
        d2 = QDateTime::fromString(time2,"yyyy-MM-dd hh:mm:ss");
        returntime2 = QDateTime::currentDateTime().addDays(10).toString("yyyy-MM-dd hh:mm:ss");
        int days = d1.daysTo(d2);
        qDebug()<<days;
        if(time1 == "")
        {
            nbookname = query.value(1).toString();
            query4.exec("SELECT 藏量 FROM book where 书名 = '"+nbookname+"' AND 校区 = '"+area+"'");
            query4.first();
            if(query4.value(0).toInt() > 0)
            {
                QMessageBox::StandardButton result = QMessageBox::question(this,"提示",tr("您预约的《%1》已有资源，是否借阅？").arg(nbookname));
                if(result == QMessageBox::Yes)
                {
                    query4.exec("UPDATE book SET 藏量=藏量-1 WHERE 书名 = '"+nbookname+"' AND 校区 = '"+area+"'");
                    query4.exec("UPDATE borrow_record SET 预约时间='"+time1+"' WHERE bookname = '"+nbookname+"' AND account = '"+account+"'");
                    query4.exec("UPDATE borrow_record SET 借书时间='"+time2+"' WHERE bookname = '"+nbookname+"' AND account = '"+account+"'");
                    query4.exec("UPDATE borrow_record SET 还书时间='"+returntime2+"' WHERE bookname = '"+nbookname+"' AND account = '"+account+"'");
                    query4.exec("UPDATE borrow_record SET 选择='y' WHERE bookname = '"+nbookname+"' AND account = '"+account+"'");
                }
            }
        }
        else if(days>20)
        {
            query2.exec("UPDATE register SET 信用='不良' WHERE account = '"+account+"'");
            goodcredit = false;
        }
        else if(days>30)
        {
            query2.exec("UPDATE register SET 状态='locked' WHERE account = '"+account+"'");
            QMessageBox::StandardButton result = QMessageBox::warning(this,"警告","您有超30天以上未还书籍，您的账户已被锁定！");
            if(result == QMessageBox::Yes||result == QMessageBox::No)
            {
                goodcredit = false;
            }
            if(!goodcredit) close();
        }
    }
    if(goodcredit)
    {
        query2.exec("UPDATE register SET 信用='良好' WHERE account = '"+account+"'");
        show();
    }
    dt->area = area;
    dt->bookTableOP();
    ui->stackedWidget->setCurrentWidget(dt);
}

void first_window_for_user::checkcredit()
{
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 信用 FROM register WHERE account = '"+account+"'");
    query.first();
    QString credit = query.value(0).toString();
    if(credit=="不良")
    {
        QMessageBox::warning(this,"警告","注意，您有逾期未还书籍，请尽快处理！");
    }
}

void first_window_for_user::on_detailBtn_clicked()
{
    dt->account = account;
    dt->area = area;
    dt->bookTableOP();
    ui->stackedWidget->setCurrentWidget(dt);
}


void first_window_for_user::on_setBtn_clicked()
{
    pp->account = account;
    pp->personalpageOP();
    ui->stackedWidget->setCurrentWidget(pp);
}


void first_window_for_user::on_noticeBtn_clicked()
{
    rn->account = account;
    rn->readnoticeOP();
    ui->stackedWidget->setCurrentWidget(rn);
}


void first_window_for_user::on_adviceBtn_clicked()
{
    al->account = account;
    ui->stackedWidget->setCurrentWidget(al);
}


void first_window_for_user::on_reserveBtn_clicked()
{
    ro->account = account;
    ro->area = area;
    ro->reserveTableOP();
    ui->stackedWidget->setCurrentWidget(ro);
}


void first_window_for_user::on_pushButton_clicked()
{
    if(!m_bSideflag)
        {
            m_propertyAnimation->setStartValue(QRect(-this->rect().width(),0,ui->sidewidget->width(),ui->sidewidget->height()));
            m_propertyAnimation->setEndValue(QRect(0,0,ui->sidewidget->width(),ui->sidewidget->height()));
            m_propertyAnimation->start();
            m_propertyAnimation2->setStartValue(QRect(-1,ui->sidewidget->height()/10,ui->pushButton->width(),ui->pushButton->height()));
            m_propertyAnimation2->setEndValue(QRect(ui->sidewidget->width()-2,ui->sidewidget->height()/10,ui->pushButton->width(),ui->pushButton->height()));
            m_propertyAnimation2->start();
            m_bSideflag = !m_bSideflag;
        }
        else
        {
            m_propertyAnimation->setStartValue(QRect(0,0,ui->sidewidget->width(),ui->sidewidget->height()));
            m_propertyAnimation->setEndValue(QRect(-this->rect().width(),0,ui->sidewidget->width(),ui->sidewidget->height()));
            m_propertyAnimation->start();
            m_propertyAnimation2->setStartValue(QRect(ui->sidewidget->width()-2,ui->sidewidget->height()/10,ui->pushButton->width(),ui->pushButton->height()));
            m_propertyAnimation2->setEndValue(QRect(-1,ui->sidewidget->height()/10,ui->pushButton->width(),ui->pushButton->height()));
            m_propertyAnimation2->start();
            m_bSideflag = !m_bSideflag;
        }
}


void first_window_for_user::on_borrowBtn_clicked()
{
    rb->account = account;
    rb->area = area;
    rb->returntableop();
    ui->stackedWidget->setCurrentWidget(rb);
}


void first_window_for_user::on_myreserveBtn_clicked()
{
    dr->account = account;
    dr->deletereservetableop();
    ui->stackedWidget->setCurrentWidget(dr);
}

