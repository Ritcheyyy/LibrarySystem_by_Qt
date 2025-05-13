#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("学生资料管理");
    setWinStyle();

    connect(ui->cancelBtn, &QPushButton::clicked, this, &MainWindow::close); // 信号槽
    connect(ui->editBtn,SIGNAL(clicked(bool)),this,SLOT(editShowDialog()));  // 信号槽

    DBO.DBOpen();
    studentTableOP();
}

MainWindow::~MainWindow()
{   delete ui;
}

void MainWindow::setWinStyle()
{   ui->tableView->setAlternatingRowColors(true); // 表格数据行隔行变色
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 单个数据格
    ui->cancelBtn->setStyleSheet(   //正常状态样式
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
    ui->okBtn->setStyleSheet(   //正常状态样式
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
    ui->editBtn->setStyleSheet(   //正常状态样式
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

}
void MainWindow::studentTableOP()
{   int i;

    tm=new QSqlTableModel(this);
    tm->setTable("person");
    ui->tableView->setModel(tm);
    tm->select();
    tm->setEditStrategy(QSqlTableModel::OnManualSubmit); // 表格数据更新数据库，要手工提交

    QString headStr[] = {"学号", "姓名", "性别", "年龄", "成绩", "隶属院系", "家庭住址"};
    int colWidths[] = {100, 100, 60, 60, 60, 180, 288};

    for(i=0; i<7; i++)
    {   tm->setHeaderData(i, Qt::Horizontal, headStr[i]); // 设置表格 column 列名称
        ui->tableView->setColumnWidth(i,  colWidths[i]); // 设置表格 column 列宽度
    }
    ui->tableView->verticalHeader()->setVisible(false); // 隐藏 row 行名称
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                     "color: brown;padding-left: 1px;border: 1px solid #6c6c6c;}");
                                                       // 设置表格 column 列的样式
    ui->tableView->horizontalHeader()->setMinimumHeight(30); // 设置表头高度
}

void MainWindow::on_okBtn_clicked()
{   tm->submitAll(); // 提交更新数据库
    close();
}

void MainWindow::on_addBtn_clicked()   // 添加空记录
{   QSqlRecord record = tm->record();  // 获取空记录
    int row = tm->rowCount();          // 获取行号
    tm->insertRecord(row, record);     // 添加空行
}

void MainWindow::editShowDialog()
{   int row = ui->tableView->currentIndex ().row(); // 获取表格当前选中行号
    if(row >= 0)
    {   QSqlRecord record= tm->record(row);  // 获取表格当前选中行的 QSqlRecord 记录
        EditDialog  editWin(this, &record);  // 定义编辑窗体
        editWin.exec();                      // 显示编辑窗体
        tm->setRecord(row, record);          // 替换编辑后的记录
        tm->submitAll();                     // 提交更新数据库
    }
    else
        QMessageBox::warning(this, "警告", "请选中需要编辑修改的数据 !");
}

void MainWindow::on_deleteBtn_clicked()
{   int row = ui->tableView->currentIndex ().row();
    if(row >= 0)
    {   QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "是否删除姓名《"+tm->record(row).value("name").toString()+"》的学生吗？");
        if(result == QMessageBox::Yes)
        {   tm->removeRow(row);               // 删除表格数据模型的记录
            tm->submitAll();                  // 提交更新数据库
        }
    }
    else
        QMessageBox::warning(this, "警告", "请选中需要删除的一行数据 !");
}

