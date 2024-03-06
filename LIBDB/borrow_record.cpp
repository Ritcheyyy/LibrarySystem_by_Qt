#include "borrow_record.h"
#include "ui_borrow_record.h"
#include "qsqlrecord.h"

borrow_record::borrow_record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::borrow_record)
{
    ui->setupUi(this);
    setWindowTitle("借阅总表");
    setGeometry(300, 100, 1000, 618);
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
    ui->search->setDefault(1);
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
    ui->addBtn->setStyleSheet(   //正常状态样式
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
    ui->addBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->deleteBtn->setStyleSheet(   //正常状态样式
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
    ui->deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
    ui->saveBtn->setStyleSheet(   //正常状态样式
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
    ui->saveBtn->setCursor(QCursor(Qt::PointingHandCursor));
    QStringList cbList;
    cbList << "按账户" << "按书名";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按账户");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

borrow_record::~borrow_record()
{
    delete ui;
}

void borrow_record::recordtableop()
{
    QLineEdit *edit = ui->findrecord;
    edit->setClearButtonEnabled(true);
    QString nafindrecord = ui->findrecord->text();
    tm=new QSqlTableModel(this);
    tm->setTable("borrow_record");
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
    QString Yes = "true";
    if(nafindrecord != "")
    {
        tm->setFilter("选择 = '"+Yes+"'");
    }
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false); // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");
                                                       // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30); // 设置表头高度
    ui->tableView->setColumnWidth(0, 320);
    ui->tableView->setColumnWidth(1, 320);
    ui->tableView->setColumnWidth(2, 320);
    ui->tableView->setColumnWidth(3, 320);
    ui->tableView->setColumnWidth(4, 0);
    ui->tableView->setColumnWidth(5, 320);
}

void borrow_record::on_addBtn_clicked()
{

}


void borrow_record::on_deleteBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString account = tm->record(row).value("account").toString();
    QString bookname = tm->record(row).value("bookname").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要删除账户（"+tm->record(row).value("account").toString()+"）的一条借阅记录？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM borrow_record where account = '"+account+"' AND bookname = '"+bookname+"'");
            delete tm;
            recordtableop();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要删除的记录！");
}


void borrow_record::on_saveBtn_clicked()
{
    tm->submitAll();
}


void borrow_record::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafindrecord = ui->findrecord->text();
    QSqlQuery query(USER.dbcon);
    if(nafindrecord != "")
    {
        query.exec("UPDATE borrow_record SET 选择 = 'false'");
        if(searchmethod == "按账户") query.prepare("SELECT ISBN FROM book");
        if(searchmethod == "按书名") query.prepare("SELECT 书名 FROM book");
        query.exec();
        while(query.next())
        {
            QString realfindrecord = query.value(0).toString();
            if(realfindrecord.contains(nafindrecord, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按书名")
                    query1.exec("UPDATE borrow_record SET 选择 = 'true' where bookname = '"+realfindrecord+"'");
                if(searchmethod == "按账户")
                    query1.exec("UPDATE borrow_record SET 选择 = 'true' where account = '"+realfindrecord+"'");
            }
        }
        if(find) recordtableop();
        else
            QMessageBox::warning(this,"错误","抱歉，没有对应的借阅记录！");
    }
    else recordtableop();
}


void borrow_record::on_back_clicked()
{
    QString nafindrecord = ui->findrecord->text();
    if(nafindrecord != "")
    {
        ui->findrecord->setText("");
        recordtableop();
    }
}

