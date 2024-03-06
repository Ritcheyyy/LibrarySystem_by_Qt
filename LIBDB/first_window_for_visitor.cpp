#include "first_window_for_visitor.h"
#include "ui_first_window_for_visitor.h"

first_window_for_visitor::first_window_for_visitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::first_window_for_visitor)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统游客访问端");
    setGeometry(200, 100, 1200, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG3.jpg"));
    connect(ui->exitBtn, &QPushButton::clicked, this, &first_window_for_visitor::close); // 信号槽
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
    ui->registerBtn->setStyleSheet(   //正常状态样式
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
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->registerBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->sidewidget->move(-ui->sidewidget->width(),0);// 左侧停靠
    ui->pushButton->move(-1,ui->sidewidget->height()/10);
    m_propertyAnimation = new QPropertyAnimation(ui->sidewidget,"geometry");
    m_propertyAnimation->setEasingCurve(QEasingCurve::InOutQuint);
    m_propertyAnimation->setDuration(300);
    m_propertyAnimation2 = new QPropertyAnimation(ui->pushButton,"geometry");
    m_propertyAnimation2->setEasingCurve(QEasingCurve::InOutQuint);
    m_propertyAnimation2->setDuration(200);
    m_bSideflag = false;
    dtv = new detailoperation_for_visitor;
    rn = new readnotice;
    ui->stackedWidget->addWidget(dtv);
    ui->stackedWidget->addWidget(rn);
}

first_window_for_visitor::~first_window_for_visitor()
{
    delete ui;
}

void first_window_for_visitor::setQLable()
{
    QString str = "欢迎您\n浏览本图书馆！";
    ui->header->setStyleSheet("QLabel{"
                              "background-color:transparent;"//设置按钮背景色
                              "border-radius:10px;"//设置圆角半径
                              "font: 700 15pt '等线';"
                              "color:white;"//设置按钮字体颜色
                              "}");
    ui->header->setProperty("text",str);
    dtv->bookTableOP();
    ui->stackedWidget->setCurrentWidget(dtv);
}

void first_window_for_visitor::on_detailBtn_clicked()
{
    dtv->account = "visitor";
    dtv->bookTableOP();
    ui->stackedWidget->setCurrentWidget(dtv);
}


void first_window_for_visitor::on_noticeBtn_clicked()
{
    rn->account = "";
    rn->readnoticeOP();
    ui->stackedWidget->setCurrentWidget(rn);
}


void first_window_for_visitor::on_registerBtn_clicked()
{
    rw = new registerwindow;
    rw->show();
    close();
}


void first_window_for_visitor::on_pushButton_clicked()
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

