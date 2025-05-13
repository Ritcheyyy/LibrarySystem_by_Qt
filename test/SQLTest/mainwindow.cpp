#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbp.DBOpen();
    connect(ui->exitBtn, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{   dbp.DBClose();
    delete ui;
}


void MainWindow::on_execBtn_clicked()
{   bool sf=false;
    QString sqlstr = ui->lineEdit->text().trimmed();
    QSqlQuery qs = dbp.DBGetData(sqlstr, sf);
    if(!sf)
    {   QMessageBox::warning(this, "警告", "SQL 语句不符合规范 !");
        return;
    }
    if(qs.isSelect())
    {   int age, score;
        ui->label_2->setText("Select 查询结果如下：");
        ui->textEdit->setText("学号\t姓名\t性别\t年龄\t成绩\t学院\n");
        while(qs.next())
        {   age = qs.value("age").toInt();
            score = qs.value("score").toInt();
            ui->textEdit->append(qs.value("num").toString()+"\t"+qs.value("name").toString()+"\t"+qs.value("sex").toString()+
                                 "\t"+tr("%1").arg(age)+"\t"+tr("%1").arg(score)+"\t"+qs.value("department").toString());
        }
    }
    else
    {   QSqlQuery qs = dbp.DBGetData("select * from person", sf);
        int age, score;
        ui->label_2->setText("Update Insert Delete 操作后更新结果如下：");
        ui->textEdit->setText("学号\t姓名\t性别\t年龄\t成绩\t学院\n");
        while(qs.next())
        {   age = qs.value("age").toInt();
            score = qs.value("score").toInt();
            ui->textEdit->append(qs.value("num").toString()+"\t"+qs.value("name").toString()+"\t"+qs.value("sex").toString()+
                                 "\t"+tr("%1").arg(age)+"\t"+tr("%1").arg(score)+"\t"+qs.value("department").toString());
        }
    }
}
