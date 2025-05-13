#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Question
{ public:
    int id;
    char ques[80];
    char ans[4][50];
    int ansok;
  public:
    Question()
    {   id = -1;
        strcpy_s(ques, ""); strcpy_s(ans[0], ""); strcpy_s(ans[1], "");
        strcpy_s(ans[2], ""); strcpy_s(ans[3], ""); ansok = 0;
    }
    Question(int uid, char *uq, char *ua0, char *ua1, char *ua2, char *ua3, int uaok)
    {   id = uid;
        strcpy_s(ques, uq);
        strcpy_s(ans[0], ua0);
        strcpy_s(ans[1], ua1);
        strcpy_s(ans[2], ua2);
        strcpy_s(ans[3], ua3);
        ansok = uaok;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getRandomTopic();
    void getOneQuestion();
    void makeScoreMessage();

private slots:
    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *BtnGroup;
    int topic[10];
    int quesCount = 0, scoreFS = 0;
    QString  scoreMessage;
    Question myques;
};
#endif // MAINWINDOW_H
