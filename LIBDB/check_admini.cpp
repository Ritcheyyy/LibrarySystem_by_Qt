#include "check_admini.h"
#include "ui_check_admini.h"

check_admini::check_admini(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_admini)
{
    ui->setupUi(this);
    setWindowTitle("管理员资格审核");
    setGeometry(300, 100, 1000, 618);
    ui->search->setDefault(1);
    USER.USEROpen();
    ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
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
    cbList << "按账号" << "按学号" << "按姓名" << "按邮箱";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf("按书名");
    if(pos < 0) pos = 0;
    ui->depcbBox->setCurrentIndex(pos);
}

check_admini::~check_admini()
{
    delete ui;
}

void check_admini::checkTableOP()
{
    QLineEdit *edit = ui->finduser;
    edit->setClearButtonEnabled(true);
    QString nafinduser = ui->finduser->text();
    tm = new QSqlTableModel(this);
    tm->setTable("admini_apply");
    tm->setEditStrategy(QSqlTableModel::OnFieldChange);
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
    ui->tableView->setColumnWidth(6,0);
    ui->tableView->setColumnWidth(0,160);
    ui->tableView->setColumnWidth(1,160);
    ui->tableView->setColumnWidth(2,160);
    ui->tableView->setColumnWidth(3,160);
    ui->tableView->setColumnWidth(4,160);
    ui->tableView->setColumnWidth(5,160);
}

void check_admini::on_back_clicked()
{
    QString nafinduser = ui->finduser->text();
    if(nafinduser != "")
    {
        ui->finduser->setText("");
        checkTableOP();
    }
}


void check_admini::on_search_clicked()
{
    bool find = false;
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString nafinduser = ui->finduser->text();
    QSqlQuery query(USER.dbcon);
    if(nafinduser != "")
    {
        query.exec("UPDATE admini_apply SET 选择 = 'false'");
        if(searchmethod == "按账号") query.prepare("SELECT 账号 FROM admini_apply");
        if(searchmethod == "按学号") query.prepare("SELECT 学号 FROM admini_apply");
        if(searchmethod == "按姓名") query.prepare("SELECT 姓名 FROM admini_apply");
        if(searchmethod == "按邮箱") query.prepare("SELECT 邮箱 FROM admini_apply");
        query.exec();
        while (query.next())
        {
            QString realfinduser = query.value(0).toString();
            if(realfinduser.contains(nafinduser, Qt::CaseSensitive))
            {
                find = true;
                QSqlQuery query1(USER.dbcon);
                if(searchmethod == "按账号")
                    query1.exec("UPDATE admini_apply SET 选择 = 'true' where 账号 = '"+realfinduser+"'");
                if(searchmethod == "按学号")
                    query1.exec("UPDATE admini_apply SET 选择 = 'true' where 学号 = '"+realfinduser+"'");
                if(searchmethod == "按姓名")
                    query1.exec("UPDATE admini_apply SET 选择 = 'true' where 姓名 = '"+realfinduser+"'");
                if(searchmethod == "按邮箱")
                    query1.exec("UPDATE admini_apply SET 选择 = 'true' where 邮箱 = '"+realfinduser+"'");
            }
        }
        if(find) checkTableOP();
        else
            QMessageBox::warning(this,"错误","抱歉，没有对应的申请！");
    }
    else checkTableOP();
}


void check_admini::on_deleteBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString theaccount = tm->record(row).value("账号").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要拒绝账户("+tm->record(row).value("账号").toString()+")的申请？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query1(USER.dbcon);
            query1.exec("DELETE FROM admini_apply where 账号 = '"+theaccount+"'");
            delete tm;
            checkTableOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要审核的记录！");
}


void check_admini::on_addBtn_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString searchmethod = ui->depcbBox->currentText().trimmed();
    QString newaccount = tm->record(row).value("账号").toString();
    QString newpassword = tm->record(row).value("密码").toString();
    QString newnum = tm->record(row).value("学号").toString();
    QString newname = tm->record(row).value("姓名").toString();
    QString newmail = tm->record(row).value("邮箱").toString();
    QString newid = tm->record(row).value("身份").toString();
    if(row >= 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "您是否要通过该申请？");
        if(result == QMessageBox::Yes)
        {
            QSqlQuery query(USER.dbcon);
            query.exec("insert into register (account,password,identification,学号,姓名,邮箱,信用,身份,状态) values ("+newaccount+" , '"+newpassword+"', 'Administrator' , '"+newnum+"', '"+newname+"', '"+newmail+"','良好','"+newid+"','unlocked');");
            query.exec("DELETE FROM admini_apply where 账号 = '"+newaccount+"'");
            delete tm;
            checkTableOP();
        }
    }
    else
        QMessageBox::warning(this, "错误", "请选中您要审核的记录！");
}

