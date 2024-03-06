#include "first_window_for_administrator.h"
#include "ui_first_window_for_administrator.h"

first_window_for_Administrator::first_window_for_Administrator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::first_window_for_Administrator)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统管理员端");
    setGeometry(200, 100, 1200, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG3.jpg"));
    connect(ui->exitBtn, &QPushButton::clicked, this, &first_window_for_Administrator::close); // 信号槽
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
    ui->checkBtn->setStyleSheet(   //正常状态样式
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
    ui->checkBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->noticeBtn->setStyleSheet(   //正常状态样式
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
    ui->noticeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBtn_2->setStyleSheet(   //正常状态样式
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
    ui->checkBtn_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->checkBtn_3->setStyleSheet(   //正常状态样式
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
    ui->checkBtn_3->setCursor(QCursor(Qt::PointingHandCursor));
    ui->setBtn->setStyleSheet(   //正常状态样式
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
    ui->editBtn->setStyleSheet(   //正常状态样式
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
    ui->editBtn->setCursor(QCursor(Qt::PointingHandCursor));
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
    ui->setBtn->setCursor(QCursor(Qt::PointingHandCursor));
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
    en = new editnotice;
    ca = new check_admini;
    eu = new edituser;
    eb = new editbook;
    ua = new user_apply;
    pp = new personalpage;
    da = new dealapply;
    br = new borrow_record;
    ui->stackedWidget->addWidget(en);
    ui->stackedWidget->addWidget(ca);
    ui->stackedWidget->addWidget(eu);
    ui->stackedWidget->addWidget(eb);
    ui->stackedWidget->addWidget(pp);
    ui->stackedWidget->addWidget(ua);
    ui->stackedWidget->addWidget(da);
    ui->stackedWidget->addWidget(br);
}

first_window_for_Administrator::~first_window_for_Administrator()
{
    delete ui;
}

void first_window_for_Administrator::setQLable()
{
    QString str;
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT 姓名 FROM register WHERE account = '"+account+"'");
    query.first();
    QString name = query.value(0).toString();
    str = "欢迎管理员"+name;
    ui->header_2->setStyleSheet("QLabel{"
                                "background-color:transparent;"//设置按钮背景色
                                "border-radius:10px;"//设置圆角半径
                                "font: 700 15pt '等线';"
                                "color:white;"//设置按钮字体颜色
                                "}");
    ui->header_2->setProperty("text",str);
    eb->bookTableOP();
    ui->stackedWidget->setCurrentWidget(eb);
}

void first_window_for_Administrator::on_noticeBtn_clicked()
{
    en->account = account;
    en->noticeTableOP();
    ui->stackedWidget->setCurrentWidget(en);
}


void first_window_for_Administrator::on_checkBtn_clicked()
{
    ca->account = account;
    ca->checkTableOP();
    ui->stackedWidget->setCurrentWidget(ca);
}


void first_window_for_Administrator::on_detailBtn_clicked()
{
    eu->account = account;
    eu->userTableOP();
    ui->stackedWidget->setCurrentWidget(eu);
}


void first_window_for_Administrator::on_editBtn_clicked()
{
    eb->account = account;
    eb->bookTableOP();
    ui->stackedWidget->setCurrentWidget(eb);
}


void first_window_for_Administrator::on_checkBtn_2_clicked()
{
    ua->user_applyOP();
    ui->stackedWidget->setCurrentWidget(ua);
}


void first_window_for_Administrator::on_setBtn_clicked()
{
    pp->account = account;
    pp->personalpageOP();
    ui->stackedWidget->setCurrentWidget(pp);
}


void first_window_for_Administrator::on_checkBtn_3_clicked()
{
    da->dealapplyOP();
    ui->stackedWidget->setCurrentWidget(da);
}


void first_window_for_Administrator::on_pushButton_clicked()
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


void first_window_for_Administrator::on_borrowBtn_clicked()
{
    br->recordtableop();
    ui->stackedWidget->setCurrentWidget(br);
}

