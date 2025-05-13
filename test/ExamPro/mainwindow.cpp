#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
#define WINWIDTH 711
#define WINHEIGHT 320

const int PLen = sizeof(Question);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("诗词大会");
    setGeometry(560, 300, WINWIDTH, WINHEIGHT);
    ui->startBtn->setStyleSheet(   //正常状态样式
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
    BtnGroup = new QButtonGroup;


    BtnGroup->addButton(ui->ARadio, 0);
    BtnGroup->addButton(ui->BRadio, 1);
    BtnGroup->addButton(ui->CRadio, 2);
    BtnGroup->addButton(ui->DRadio, 3);
    BtnGroup->setExclusive(true);
    getRandomTopic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getRandomTopic()
{   bool flag;
    srand(time(0));
    for(int i = 0; i < 10; i ++)
    {   flag = true;
        while(flag)
        {   flag = false;
            topic[i] = (int)((rand()+100)*777)%20+1;
            for(int j = 0; j < i; j ++)
            {   if(topic[i] == topic[j])
                {   flag = true;
                    break;
                }
            }
        }
    }
    for(int i=0; i<10; i++)
        qDebug() << topic[i] << "  ";
    quesCount = 0; scoreFS = 0;
    scoreMessage="";
}

void MainWindow::getOneQuestion()
{   std::ifstream ifile("D:\\desktop\\Assignment\\ExamPro\\examdata.dat", std::ios::in|std::ios::binary);
    if(!ifile)
    {   qDebug() << "文件 examdata.dat 打开失败!";
        exit(1);
    }

    if(quesCount >= 1)
        makeScoreMessage();
    quesCount ++;
    if(quesCount == 11)
    {   scoreMessage.append("  ------------------------------------------------------------------------------------------------\n");
        scoreMessage.append("       最终成绩："+tr("%1").arg(scoreFS));
        ui->textEdit->setText("");
        QMessageBox::information(this, "成绩显示", scoreMessage);
        scoreMessage = "";
        getRandomTopic();
        ui->ARadio->setText("A ");  ui->BRadio->setText("B ");
        ui->CRadio->setText("C ");  ui->DRadio->setText("D ");
        ui->startBtn->setText("重新开始");
        BtnGroup->setExclusive(false);
        ui->ARadio->setChecked(false); ui->BRadio->setChecked(false);
        ui->CRadio->setChecked(false); ui->DRadio->setChecked(false);
        BtnGroup->setExclusive(true);
        return;
    }

    ifile.seekg(PLen * (topic[quesCount-1]-1));
    ifile.read((char *)&myques, PLen);
    ui->textEdit->setText("\n  "+tr("%1").arg(quesCount)+".  "+QString::fromLocal8Bit(myques.ques));

    ui->ARadio->setText("A "+QString::fromLocal8Bit(myques.ans[0]));
    ui->BRadio->setText("B "+QString::fromLocal8Bit(myques.ans[1]));
    ui->CRadio->setText("C "+QString::fromLocal8Bit(myques.ans[2]));
    ui->DRadio->setText("D "+QString::fromLocal8Bit(myques.ans[3]));
    BtnGroup->setExclusive(false);
    ui->ARadio->setChecked(false);
    ui->BRadio->setChecked(false);
    ui->CRadio->setChecked(false);
    ui->DRadio->setChecked(false);
    BtnGroup->setExclusive(true);
    ifile.close();

}

void MainWindow::makeScoreMessage()
{   QString ss = "\n  "+tr("%1").arg(quesCount)+".  "+QString::fromLocal8Bit(myques.ques)+"\n";
    scoreMessage.append(ss);

    QString okorno = "×";
    QString astr = "    A ";
    QString bstr = "    B ";
    QString cstr = "    C ";
    QString dstr = "    D ";
    if(ui->ARadio->isChecked() && myques.ansok == 0)
    {   scoreFS += 10;
        okorno =  "√";
    }
    if(ui->BRadio->isChecked() && myques.ansok == 1)
    {   scoreFS += 10;
        okorno =  "√";
    }
    if(ui->CRadio->isChecked() && myques.ansok == 2)
    {   scoreFS += 10;
        okorno =  "√";
    }
    if(ui->DRadio->isChecked() && myques.ansok == 3)
    {   scoreFS += 10;
        okorno =  "√";
    }

    if(ui->ARadio->isChecked())  astr = "   (A)";
    if(ui->BRadio->isChecked())  bstr = "   (B)";
    if(ui->CRadio->isChecked())  cstr = "   (C)";
    if(ui->DRadio->isChecked())  dstr = "   (D)";

    QString ssans = "  "+okorno+astr+QString::fromLocal8Bit(myques.ans[0])+
                                bstr+QString::fromLocal8Bit(myques.ans[1])+
                                cstr+QString::fromLocal8Bit(myques.ans[2])+
                                dstr+QString::fromLocal8Bit(myques.ans[3])+"\n";
    scoreMessage.append(ssans);
}

void MainWindow::on_startBtn_clicked()
{   ui->startBtn->setText("下一题");
    getOneQuestion();
}

