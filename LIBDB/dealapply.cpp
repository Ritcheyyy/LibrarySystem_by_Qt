#include "dealapply.h"
#include "qsqlrecord.h"
#include "ui_dealapply.h"

dealapply::dealapply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dealapply)
{
    ui->setupUi(this);
    setWindowTitle("用户建议栏");
    setGeometry(300, 100, 1000, 618);
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
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
    USER.USEROpen();
}

dealapply::~dealapply()
{
    delete ui;
}

void dealapply::dealapplyOP()
{
    if(tm) tm=NULL;
    tm = new QSqlTableModel(this);
    tm->setTable("advice");
    tm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false);    // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");    // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30);    // 设置表头高度
    ui->tableView->setColumnWidth(0,350);
    ui->tableView->setColumnWidth(1,621);
}

void dealapply::on_deleteBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString theaccount = tm->record(row).value("建议").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要删除该建议？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM advice where 建议 = '"+theaccount+"'");
            delete tm;
            dealapplyOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要处理的申诉！");
}

