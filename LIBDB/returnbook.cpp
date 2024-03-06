#include "returnbook.h"
#include "ui_returnbook.h"
#include "detailoperation.h"
#include <QMessageBox>

returnbook::returnbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::returnbook)
{
    ui->setupUi(this);
    setWindowTitle("用户还书服务");
    setGeometry(300, 100, 1000, 618);
    ui->againBtn->setStyleSheet(   //正常状态样式
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
    ui->returnBtn->setStyleSheet(   //正常状态样式
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
    USER.USEROpen();
}

returnbook::~returnbook()
{
    delete ui;
}

void returnbook::returntableop()
{
    tm=new QSqlTableModel(this);
    tm->setTable("borrow_record");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
    tm->setFilter(QString("account = '%1' and 选择 = '%2'").arg(account).arg("y"));
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false); // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");
                                                       // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30); // 设置表头高度
    ui->tableView->setColumnWidth(0, 0);
    ui->tableView->setColumnWidth(1, 320);
    ui->tableView->setColumnWidth(2, 320);
    ui->tableView->setColumnWidth(3, 0);
    ui->tableView->setColumnWidth(4, 0);
    ui->tableView->setColumnWidth(5, 320);
}


void returnbook::on_returnBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString bookname = tm->record(row).value("bookname").toString();    //书名
    QString time = tm->record(row).value("借书时间").toString();
    if(row >= 0&&time!="")
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要归还《"+tm->record(row).value("bookname").toString()+"》？");
        if(result == QMessageBox::Yes)
        {
            tm->removeRow(row);
            QSqlQuery query(USER.dbcon);
            query.exec("UPDATE book SET 藏量=藏量+1 WHERE 书名='"+bookname+"' AND 校区='"+area+"'");
            query.exec("UPDATE register SET 当前借书=当前借书-1 WHERE account='"+account+"'");
            query.exec("DELETE FROM borrow_record WHERE bookname ='"+bookname+"' ");
            delete tm;
            returntableop();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要归还的书！");
}


void returnbook::on_againBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString bookname = tm->record(row).value("bookname").toString();    //书名
    QString time = tm->record(row).value("还书时间").toString();
    QDateTime d1 = QDateTime::fromString(time,"yyyy-MM-dd hh:mm:ss");
    time = d1.addDays(10).toString("yyyy-MM-dd hh:mm:ss");
    if(row >= 0&&time!="")
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要续借《"+tm->record(row).value("bookname").toString()+"》？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query(USER.dbcon);
            query.prepare("UPDATE borrow_record SET 还书时间 = '"+time+"' WHERE bookname ='"+bookname+"' AND account = '"+account+"'");
            query.exec();
            delete tm;
            returntableop();
            QMessageBox::warning(this, "提示", "续借成功，请按时归还！");
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要续借的书！");
}

