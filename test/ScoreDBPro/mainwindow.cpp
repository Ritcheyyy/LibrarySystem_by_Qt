#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("高考成绩查询");
    ui->exitBtn->setStyleSheet(   //正常状态样式
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
    QStringList sfList;
    sfList.append("北京"); sfList.append("上海"); sfList.append("浙江"); sfList.append("广东"); sfList.append("江苏");
    sfList.append("福建"); sfList.append("安徽"); sfList.append("河南"); sfList.append("黑龙江"); sfList.append("四川");
    sfList.append("重庆"); sfList.append("云南"); sfList.append("新疆"); sfList.append("江西"); sfList.append("湖南");
    sfList.append("湖北"); sfList.append("广西"); sfList.append("西藏"); sfList.append("辽宁"); sfList.append("天津");

    QStringListModel *sfListMode = new QStringListModel(sfList);
    ui->listView->setModel(sfListMode);
    ui->listView->setSpacing(3);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->exitBtn, &QPushButton::clicked, this, &MainWindow::close);
    DBO.DBOpen();
    ScoreDBDataGet("北京");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ScoreDBDataGet(QString usf)
{   QString sqlstr = "SELECT xh,name,xb,age,sf,dq,mz,yw,yy,sx,yw+yy+sx as zf FROM student where sf= '"+usf+"'";
    QSqlQuery qq = DBO.DBGetData(sqlstr);
    QSqlQueryModel *qm=new QSqlQueryModel(this);
    int onesum=0, count=0, max=0, min=1000, allsum=0;
    qq.first();
    while(qq.next())
    {   onesum = qq.value("yw").toInt()+qq.value("sx").toInt()+qq.value("yy").toInt();
        if(onesum > max) max = onesum;
        if(onesum < min) min = onesum;
        allsum += onesum;
        count ++;
    }
    if(count != 0)
        ui->textEdit->setText(" 省  份："+usf+"\n\n 最高分："+tr("%1").arg(max)+"\n 最低分："+tr("%1").arg(min)+"\n 平均分："+tr("%1").arg((int)allsum/count));
    else
        ui->textEdit->setText(" 省  份："+usf+"\n\n 无学生数据！");
    qm->setQuery(sqlstr);
    qm->setHeaderData(0, Qt::Horizontal, "学号");
    qm->setHeaderData(1, Qt::Horizontal, "姓名");
    qm->setHeaderData(2, Qt::Horizontal, "性别");
    qm->setHeaderData(3, Qt::Horizontal, "年龄");
    qm->setHeaderData(4, Qt::Horizontal, "省份");
    qm->setHeaderData(5, Qt::Horizontal, "地区");
    qm->setHeaderData(6, Qt::Horizontal, "民族");
    qm->setHeaderData(7, Qt::Horizontal, "语文");
    qm->setHeaderData(8, Qt::Horizontal, "英语");
    qm->setHeaderData(9, Qt::Horizontal, "数学");
    qm->setHeaderData(10, Qt::Horizontal, "总分");
    ui->tableView->setModel(qm);
    ui->tableView->setColumnWidth(0,  80);
    ui->tableView->setColumnWidth(1,  80);
    ui->tableView->setColumnWidth(2,  40);
    ui->tableView->setColumnWidth(3,  40);
    ui->tableView->setColumnWidth(4,  80);
    ui->tableView->setColumnWidth(5,  100);
    ui->tableView->setColumnWidth(6,  60);
    ui->tableView->setColumnWidth(7,  59);
    ui->tableView->setColumnWidth(8,  59);
    ui->tableView->setColumnWidth(9,  59);
    ui->tableView->setColumnWidth(10,  60);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");
    ui->tableView->horizontalHeader()->setMinimumHeight(25);
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString sf =index.data().toString().trimmed();
    ScoreDBDataGet(sf);
}

