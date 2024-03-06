#include <QMessageBox>
#include "editnotice.h"
#include "ui_editnotice.h"

editnotice::editnotice(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::editnotice)
{
    ui->setupUi(this);
    setWindowTitle("通知编辑");
    setGeometry(600, 100, 400, 600);
    USER.USEROpen();
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
    ui->newnotice->setStyleSheet(   //正常状态样式
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
    ui->newnotice->setCursor(QCursor(Qt::PointingHandCursor));
    ui->deletenotice->setStyleSheet(   //正常状态样式
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
    ui->deletenotice->setCursor(QCursor(Qt::PointingHandCursor));
    ui->save->setStyleSheet(   //正常状态样式
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
    ui->save->setCursor(QCursor(Qt::PointingHandCursor));
}

editnotice::~editnotice()
{
    delete ui;
}

void editnotice::noticeTableOP()
{
    tm = new QSqlTableModel(this);
    tm->setTable("notice");
    tm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false);    // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");    // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(430);
    ui->tableView->setColumnWidth(0,380);
}

void editnotice::on_newnotice_clicked()
{
    QSqlRecord record = tm->record();  // 获取空记录
    int row = tm->rowCount();          // 获取行号
    tm->insertRecord(row, record);     // 添加空行
}


void editnotice::on_deletenotice_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString notice = tm->record(row).value("通知").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要删除"+tm->record(row).value("通知").toString()+"？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM notice where 通知 = '"+notice+"'");
            delete tm;
            noticeTableOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要删除的通知！");
}


void editnotice::on_save_clicked()
{
    tm->submitAll();
    noticeTableOP();
}

