#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <string>
#include "detailoperation_for_visitor.h"
#include "ui_detailoperation_for_visitor.h"
using namespace std;

detailoperation_for_visitor::detailoperation_for_visitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailoperation_for_visitor)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统");
    setGeometry(300, 100, 1000, 618);
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
    ui->search->setDefault(1);
    ui->registerBtn->setStyleSheet(   //正常状态样式
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
    ui->registerBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->back->setStyleSheet(   //正常状态样式
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
    ui->back->setCursor(QCursor(Qt::PointingHandCursor));
    ui->search->setStyleSheet(   //正常状态样式
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
    ui->search->setCursor(QCursor(Qt::PointingHandCursor));
    QStringList cbList;
    cbList << "按书名" << "按ISBN" << "按作者" << "按出版社" << "按分类" << "按校区";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按书名");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

detailoperation_for_visitor::~detailoperation_for_visitor()
{
    delete ui;
}

void detailoperation_for_visitor::bookTableOP()
{
    QLineEdit *edit = ui->findbook;
    edit->setClearButtonEnabled(true);
    QString nafindbook = ui->findbook->text();
    tm = new QSqlTableModel(this);
    tm->setTable("book");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
    QString Yes = "true";
    if(nafindbook != "")
    {
        tm->setFilter("选择 = '"+Yes+"'");
    }
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false);    // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");    // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30);    // 设置表头高度
    ui->tableView->setColumnWidth(4,0);
    ui->tableView->setColumnWidth(9,0);
}

void detailoperation_for_visitor::on_back_clicked()
{
    QString nafindbook = ui->findbook->text();
    if(nafindbook != "")
    {
        ui->findbook->setText("");
        bookTableOP();
    }
}

void detailoperation_for_visitor::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafindbook = ui->findbook->text();
    QSqlQuery query(USER.dbcon);
    if(nafindbook != "")
    {
        query.exec("UPDATE book SET 选择 = 'false'");
        if(searchmethod == "按书名") query.prepare("SELECT 书名 FROM book");
        if(searchmethod == "按ISBN") query.prepare("SELECT ISBN FROM book");
        if(searchmethod == "按作者") query.prepare("SELECT 作者 FROM book");
        if(searchmethod == "按出版社") query.prepare("SELECT 出版社 FROM book");
        if(searchmethod == "按分类") query.prepare("SELECT 建议上架 FROM book");
        if(searchmethod == "按校区") query.prepare("SELECT 校区 FROM book");
        query.exec();
        while(query.next())
        {
            QString realfindbook = query.value(0).toString();
            if(realfindbook.contains(nafindbook, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按书名")
                    query1.exec("UPDATE book SET 选择 = 'true' where 书名 = '"+realfindbook+"'");
                if(searchmethod == "按ISBN")
                    query1.exec("UPDATE book SET 选择 = 'true' where ISBN = '"+realfindbook+"'");
                if(searchmethod == "按作者")
                    query1.exec("UPDATE book SET 选择 = 'true' where 作者 = '"+realfindbook+"'");
                if(searchmethod == "按出版社")
                    query1.exec("UPDATE book SET 选择 = 'true' where 出版社 = '"+realfindbook+"'");
                if(searchmethod == "按分类")
                    query1.exec("UPDATE book SET 选择 = 'true' where 建议上架 = '"+realfindbook+"'");
                if(searchmethod == "按校区")
                    query1.exec("UPDATE book SET 选择 = 'true' where 校区 = '"+realfindbook+"'");
            }
        }
        if(find) bookTableOP();
        else
            QMessageBox::warning(this,"错误","抱歉，没有对应的资源！");
    }
    else bookTableOP();
}

void detailoperation_for_visitor::on_registerBtn_clicked()
{
    rw = new registerwindow;
    rw->show();
    close();
}

