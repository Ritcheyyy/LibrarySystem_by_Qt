#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统");
    setGeometry(600, 100, 450, 600);
    ui->label->setPixmap(QPixmap("C:/LIBDB/BG.png"));
    ui->login->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#56b1c8;"//设置按钮背景色
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#569ac8;"
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->login->setCursor(QCursor(Qt::PointingHandCursor));
    ui->register_2->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#20c6f8;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#209af8;"
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->register_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->visitorLogin->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#15a611;"//设置按钮背景色
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:10px;"//设置圆角半径
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#159a11;"
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->visitorLogin->setCursor(QCursor(Qt::PointingHandCursor));
    ui->exitbutton->setStyleSheet(   //正常状态样式
                         "QPushButton{"
                         "background-color:#88a600;"//设置按钮背景色
                         "border-radius:10px;"//设置圆角半径
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "color:white;"//设置按钮字体颜色
                         "}"
                         //鼠标悬停样式
                         "QPushButton:hover{"
                         "background-color:#889a00;"
                         "font: 700 15pt '等线';"
                         "background-color:transparent;"
                         "border-radius:15px;"//设置圆角半径
                         "color:red;"
                         "}");
    ui->exitbutton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(ui->exitbutton,&QPushButton::clicked,this,&QWidget::close);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_register_2_clicked()
{
    re = new registerwindow;
    re->show();
}


void MainWindow::on_login_clicked()
{
    lw = new loginwindow;
    lw->show();
}

void MainWindow::on_visitorLogin_clicked()
{
    fv = new first_window_for_visitor;
    fv->setQLable();
    fv->show();
}
