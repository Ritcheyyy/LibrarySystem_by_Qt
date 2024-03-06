#include "reserveoperation.h"
#include "ui_reserveoperation.h"

reserveoperation::reserveoperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserveoperation)
{
    ui->setupUi(this);
    setWindowTitle("图书预约系统");
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
    QStringList cbList;
    cbList << "按书名" << "按ISBN" << "按作者" << "按出版社" << "按分类";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按书名");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

reserveoperation::~reserveoperation()
{
    delete ui;
}

void reserveoperation::reserveTableOP()
{
    if(tm) tm=NULL;
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

void reserveoperation::on_search_clicked()
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
        if(searchmethod == "按分类") query.prepare("SELECT 分类 FROM book");
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
            }
        }
        if(find) reserveTableOP();
        else
            QMessageBox::warning(this,"错误","抱歉，没有对应的资源,请于“图书馆信箱”提供您想要的资源的信息！");
    }
    else reserveTableOP();
}

void reserveoperation::on_borrowBtn_clicked()    //我要预约
{
    QSqlQuery query0(USER.dbcon);
    query0.exec("SELECT 信用,状态 FROM register WHERE account = '"+account+"'");
    query0.first();
    QString credit = query0.value(0).toString();
    QString state = query0.value(1).toString();
    if(credit=="不良")
    {
        QMessageBox::warning(this,"警告","您的用户信用情况欠佳！");
    }
    else if(state == "locked")
    {
        QMessageBox::warning(this,"警告","您的账户已被锁定！");
    }
    else
    {
    int row = ui->tableView->currentIndex().row();
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
    if(row >= 0&&ok==true)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要预约《"+tm->record(row).value("书名").toString()+"》？");
        if(result == QMessageBox::Yes)
        {
            if(num_of_book>0)
            {
                QString datetime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QSqlQuery query0(USER.dbcon);
                query0.prepare("insert into borrow_record (account,bookname,预约时间,选择) values ('"+account+"' , '"+bookname+"' , '"+datetime+"' , 'n');");
                query0.exec();
                query0.prepare("UPDATE register SET 当前借书=当前借书+1 WHERE account = '"+account+"'");
                query0.exec();
            }
            else
            {
                QMessageBox::warning(this,"错误","抱歉，没有对应的资源,请于“图书馆信箱”提供您想要的资源的信息！");
            }
        }
    }
    else if(row<0)
        QMessageBox::warning(this, "错误", "请选中您想预约的书！");
    else if(ok==false)
        QMessageBox::warning(this, "错误", "您已经预约过这本书了！");
    }
}

void reserveoperation::on_back_clicked()
{
    QString nafindbook = ui->findbook->text();
    if(nafindbook != "")
    {
        ui->findbook->setText("");
        reserveTableOP();
    }
}


