#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <string>
#include "detailoperation.h"
#include "ui_detailoperation.h"
using namespace std;

detailoperation::detailoperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailoperation)
{
    ui->setupUi(this);
    setWindowTitle("图书管理系统");
    setGeometry(300, 100, 1000, 618);
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
    ui->search->setDefault(1);
    ui->borrowBtn->setStyleSheet(   //正常状态样式
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
    ui->borrowBtn->setCursor(QCursor(Qt::PointingHandCursor));
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
    cbList << "按书名" << "按ISBN" << "按作者" << "按出版社" << "按分类";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按书名");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

detailoperation::~detailoperation()
{
    delete ui;
}

void detailoperation::bookTableOP()
{
    if(tm) tm=NULL;
    QLineEdit *edit = ui->findbook;
    edit->setClearButtonEnabled(true);
    QString nafindbook = ui->findbook->text();
    tm = new QSqlTableModel(this);
    tm->setTable("book");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
    tm->setFilter("校区 = '"+area+"'");
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

void detailoperation::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafindbook = ui->findbook->text();
    QSqlQuery query(USER.dbcon);
    if(nafindbook != "")
    {
        query.exec("UPDATE book SET 选择 = 'false'");
        if(searchmethod == "按书名") query.prepare("SELECT 书名 FROM book WHERE 校区 = '"+area+"'");
        if(searchmethod == "按ISBN") query.prepare("SELECT ISBN FROM book WHERE 校区 = '"+area+"'");
        if(searchmethod == "按作者") query.prepare("SELECT 作者 FROM book WHERE 校区 = '"+area+"'");
        if(searchmethod == "按出版社") query.prepare("SELECT 出版社 FROM book WHERE 校区 = '"+area+"'");
        if(searchmethod == "按分类") query.prepare("SELECT 建议上架 FROM book WHERE 校区 = '"+area+"'");
        query.exec();
        while(query.next())
        {
            QString realfindbook = query.value(0).toString();
            if(realfindbook.contains(nafindbook, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按书名")
                    query1.exec("UPDATE book SET 选择 = 'true' where 书名 = '"+realfindbook+"' AND 校区 = '"+area+"'");
                if(searchmethod == "按ISBN")
                    query1.exec("UPDATE book SET 选择 = 'true' where ISBN = '"+realfindbook+"' AND 校区 = '"+area+"'");
                if(searchmethod == "按作者")
                    query1.exec("UPDATE book SET 选择 = 'true' where 作者 = '"+realfindbook+"' AND 校区 = '"+area+"'");
                if(searchmethod == "按出版社")
                    query1.exec("UPDATE book SET 选择 = 'true' where 出版社 = '"+realfindbook+"' AND 校区 = '"+area+"'");
                if(searchmethod == "按分类")
                    query1.exec("UPDATE book SET 选择 = 'true' where 建议上架 = '"+realfindbook+"' AND 校区 = '"+area+"'");
            }
        }
        if(find) bookTableOP();
        else
        {
            QMessageBox::warning(this,"错误","抱歉，没有对应的资源,请您前往“图书预约”搜索更多书籍！");
        }
    }
    else bookTableOP();
}

void detailoperation::on_borrowBtn_clicked()    //我要借书
{
    QSqlQuery query0(USER.dbcon);
    query0.exec("SELECT 信用,状态 FROM register WHERE account = '"+account+"'");
    query0.first();
    QString credit = query0.value(0).toString();
    QString state = query0.value(1).toString();
    query0.exec("SELECT 当前借书 FROM register WHERE account = '"+account+"'");
    query0.first();
    int num = query0.value(0).toInt();
    if(credit=="不良")
    {
        QMessageBox::warning(this,"警告","您的用户信用情况欠佳！");
    }
    else
    {
    int row = ui->tableView->currentIndex().row();
    int col = 4;    //第五列是藏量，从第零列开始，col=4
    QSqlRecord record = tm->record(row);
    QString bookname = tm->record(row).value("书名").toString();    //书名
    int num_of_book = record.value("藏量").toInt();    //原本书的数量
    QSqlQuery query(USER.dbcon);
    query.exec("SELECT bookname FROM borrow_record WHERE account = '"+account+"'");
    bool ok = true;
    while(query.next())
    {
        if(query.value(0).toString()==bookname)
        {
           ok=false;
        }
    }
    QSqlQuery query5(USER.dbcon);
    query5.exec("SELECT 藏量 FROM book WHERE 书名 = '"+bookname+"' AND 校区 = '"+area+"'");
    query5.first();
    int booknum = query5.value(0).toInt();
    if(booknum <= 0)
    {
        QMessageBox::warning(this, "警告", "该书暂无资源！");
    }
    else if(row >= 0&&ok==true&&state=="unlocked")
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要借《"+tm->record(row).value("书名").toString()+"》？");
        if(result == QMessageBox::Yes)
        {
            if(num_of_book>0)
            {
                QString datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString returntime = QDateTime::currentDateTime().addDays(10).toString("yyyy-MM-dd hh:mm:ss");
                tm->setData(tm->index(row,col),num_of_book-1);    //设定只能借一本了
                QSqlQuery query0(USER.dbcon);
                query0.prepare("insert into borrow_record (account,bookname,借书时间,选择,还书时间) values ('"+account+"' , '"+bookname+"' , '"+datetime+"' , 'y' , '"+returntime+"');");
                query0.exec();
                query.prepare("UPDATE register SET 当前借书=当前借书+1 WHERE account='"+account+"'");
                query.exec();
            }
        }
    }
    else if(num>=10)
    {
        QMessageBox::warning(this,"提示","抱歉，您的账户目前借书已超过十本！");
    }
    else if(state=="locked")
    {
        QMessageBox::warning(this,"错误","您的账户已被锁定！");
    }
    else if(row<0)
        QMessageBox::warning(this, "错误", "请选中您想借的书！");
    else if(ok==false)
        QMessageBox::warning(this, "错误", "您已经借过这本书了！");
    }
}

void detailoperation::on_back_clicked()
{
    QString nafindbook = ui->findbook->text();
    if(nafindbook != "")
    {
        ui->findbook->setText("");
        bookTableOP();
    }
}

