#include "readnotice.h"
#include "ui_readnotice.h"

readnotice::readnotice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readnotice)
{
    ui->setupUi(this);
    setWindowTitle("图书馆通知");
    setGeometry(600, 100, 400, 600);
    USER.USEROpen();
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
}

readnotice::~readnotice()
{
    delete ui;
}

void readnotice::readnoticeOP()
{

    tm = new QSqlTableModel(this);
    tm->setTable("notice");
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false);    // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");    // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(400);
}
