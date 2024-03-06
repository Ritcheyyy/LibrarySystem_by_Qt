#include "user_apply.h"
#include "qsqlrecord.h"
#include "ui_user_apply.h"

user_apply::user_apply(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_apply)
{
    ui->setupUi(this);
    setWindowTitle("用户申诉管理");
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
    QStringList cbList;
    cbList << "按账号" << "按姓名" << "按学号" << "按注册时间";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按账号");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

user_apply::~user_apply()
{
    delete ui;
}

void user_apply::user_applyOP()
{
    if(tm) tm=NULL;
    QLineEdit *edit = ui->finduser;
    edit->setClearButtonEnabled(true);
    QString nafinduser = ui->finduser->text();
    tm = new QSqlTableModel(this);
    tm->setTable("request");
    tm->setEditStrategy(QSqlTableModel::OnManualSubmit);
    QString Yes = "true";
    if(nafinduser != "")
    {
        tm->setFilter("选择 = '"+Yes+"'");
    }
    tm->select();
    ui->tableView->setModel(tm);
    ui->tableView->verticalHeader()->setVisible(false);    // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");    // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30);    // 设置表头高度
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->setColumnWidth(2,120);
    ui->tableView->setColumnWidth(3,120);
    ui->tableView->setColumnWidth(4,120);
    ui->tableView->setColumnWidth(5,120);
    ui->tableView->setColumnWidth(6,120);
    ui->tableView->setColumnWidth(7,120);
    ui->tableView->setColumnWidth(8,0);
}

void user_apply::on_deleteBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString theaccount = tm->record(row).value("账号").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要删除该申请？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM request where 账号 = '"+theaccount+"'");
            delete tm;
            user_applyOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要处理的申诉！");
}


void user_apply::on_back_clicked()
{
    QString nafinduser = ui->finduser->text();
    if(nafinduser != "")
    {
        ui->finduser->setText("");
        user_applyOP();
    }
}


void user_apply::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafinduser = ui->finduser->text();
    QSqlQuery query(USER.dbcon);
    if(nafinduser != "")
    {
        query.exec("UPDATE request SET 选择 = 'false'");
        if(searchmethod == "按账号") query.prepare("SELECT 账号 FROM request");
        if(searchmethod == "按学号") query.prepare("SELECT 学号 FROM request");
        if(searchmethod == "按姓名") query.prepare("SELECT 姓名 FROM request");
        if(searchmethod == "按注册时间") query.prepare("SELECT 注册时间 FROM request");
        query.exec();
        while (query.next())
        {
            QString realfinduser = query.value(0).toString();
            if(realfinduser.contains(nafinduser, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按账号")
                    query1.exec("UPDATE request SET 选择 = 'true' where 账号 = '"+realfinduser+"'");
                if(searchmethod == "按学号")
                    query1.exec("UPDATE request SET 选择 = 'true' where 学号 = '"+realfinduser+"'");
                if(searchmethod == "按姓名")
                    query1.exec("UPDATE request SET 选择 = 'true' where 姓名 = '"+realfinduser+"'");
                if(searchmethod == "按注册时间")
                    query1.exec("UPDATE request SET 选择 = 'true' where 注册时间 = '"+realfinduser+"'");
            }
        }
        if(find) user_applyOP();
        else
            QMessageBox::warning(this,"错误","该用户的申请不存在！");
    }
    else user_applyOP();
}

