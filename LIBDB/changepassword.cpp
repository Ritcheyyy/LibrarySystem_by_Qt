#include "changepassword.h"
#include "ui_changepassword.h"

#include <QTimer>
#include <QWidget>
#include <qfont.h>

changepassword::changepassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changepassword)
{
    ui->setupUi(this);
    setGeometry(735, 170, 300, 60);
    this->setWindowFlags(Qt::FramelessWindowHint
                         | Qt::Tool
                         | Qt::WindowStaysOnTopHint);
    this->setStyleSheet("color:red");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_DeleteOnClose); // 关闭即销毁
    ui->label->setText("修改成功！");
    QFont ft;
    ft.setPointSize(12);
    ui->label->setFont(ft);
    QTimer* timer = new QTimer(this);
    timer->start(1500);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeupDestroy()));
}

changepassword::~changepassword()
{
    delete ui;
}
