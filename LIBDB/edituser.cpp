#include "edituser.h"
#include "ui_edituser.h"
#include<qsqlrecord.h>

edituser::edituser(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::edituser)
{
    ui->setupUi(this);
    setWindowTitle("用户信息管理");
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
    QStringList cbList;
    cbList << "按账号" << "按学号" << "按姓名" << "按信用" << "按校区";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按账号");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
    USER.USEROpen();
}

edituser::~edituser()
{
    delete ui;
}

void edituser::userTableOP()
{
    QString id = "user";
    QLineEdit *edit = ui->finduser;
    edit->setClearButtonEnabled(true);
    QString nafinduser = ui->finduser->text();
    tm = new QSqlTableModel(this);
    tm->setTable("register");
    tm->setFilter("identification = '"+id+"'");
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
    ui->tableView->setColumnWidth(13,0);
}

void edituser::on_back_clicked()
{
    QString nafinduser = ui->finduser->text();
    if(nafinduser != "")
    {
        ui->finduser->setText("");
        userTableOP();
    }
}


void edituser::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafinduser = ui->finduser->text();
    QSqlQuery query(USER.dbcon);
    if(nafinduser != "")
    {
        query.exec("UPDATE register SET 选择 = 'false'");
        if(searchmethod == "按账号") query.prepare("SELECT account FROM register");
        if(searchmethod == "按学号") query.prepare("SELECT 学号 FROM register");
        if(searchmethod == "按姓名") query.prepare("SELECT 姓名 FROM register");
        if(searchmethod == "按信用") query.prepare("SELECT 信用 FROM register");
        if(searchmethod == "按校区") query.prepare("SELECT 校区 FROM register");
        query.exec();
        while (query.next())
        {
            QString realfinduser = query.value(0).toString();
            if(realfinduser.contains(nafinduser, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按账号")
                    query1.exec("UPDATE register SET 选择 = 'true' where account = '"+realfinduser+"'");
                if(searchmethod == "按学号")
                    query1.exec("UPDATE register SET 选择 = 'true' where 学号 = '"+realfinduser+"'");
                if(searchmethod == "按姓名")
                    query1.exec("UPDATE register SET 选择 = 'true' where 姓名 = '"+realfinduser+"'");
                if(searchmethod == "按信用")
                    query1.exec("UPDATE register SET 选择 = 'true' where 信用 = '"+realfinduser+"'");
                if(searchmethod == "按校区")
                    query1.exec("UPDATE register SET 选择 = 'true' where 校区 = '"+realfinduser+"'");
            }
        }
        if(find) userTableOP();
        else
            QMessageBox::warning(this,"错误","用户不存在！");
    }
    else userTableOP();
}


void edituser::on_deleteBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString theaccount = tm->record(row).value("account").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要注销账户("+tm->record(row).value("account").toString()+")？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM register where account = '"+theaccount+"'");
            delete tm;
            userTableOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要注销的账户！");
}


void edituser::on_saveBtn_clicked()
{
    tm->submitAll();
    userTableOP();
}

