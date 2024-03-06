#include "deletereserve.h"
#include "ui_deletereserve.h"
#include "reserveoperation.h"
#include <QMessageBox>

deletereserve::deletereserve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deletereserve)
{
    ui->setupUi(this);
    setWindowTitle("用户取消预约服务");
    setGeometry(300, 100, 1000, 618);
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
    ui->returnBtn->setCursor(QCursor(Qt::PointingHandCursor));
    USER.USEROpen();
}

deletereserve::~deletereserve()
{
    delete ui;
}

void deletereserve::deletereservetableop()
{
    tm=new QSqlTableModel(this);
    tm->setTable("borrow_record");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
    tm->setFilter(QString("account = '%1' and 选择 = '%2'").arg(account).arg("n"));
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false); // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");
                                                       // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30); // 设置表头高度
    ui->tableView->setColumnWidth(0, 0);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 0);
    ui->tableView->setColumnWidth(3, 600);
    ui->tableView->setColumnWidth(4, 0);
    ui->tableView->setColumnWidth(5, 0);
}

void deletereserve::on_returnBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString bookname = tm->record(row).value("bookname").toString();    //书名
    QString time = tm->record(row).value("借书时间").toString();
    if(row >= 0&&time=="")
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "提示", "您是否取消《"+tm->record(row).value("bookname").toString()+"》的预约？");
        if(result == QMessageBox::Yes)
        {
            tm->removeRow(row);
            QSqlQuery query(USER.dbcon);
            query.prepare("DELETE FROM borrow_record WHERE bookname = '"+bookname+"'");
            query.exec();
            delete tm;
            deletereservetableop();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要取消预约的书！");
}

