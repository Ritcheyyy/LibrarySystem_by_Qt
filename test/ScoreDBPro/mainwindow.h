#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DBOperator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ScoreDBDataGet(QString usf);

private slots:
    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DBOperator DBO;
};
#endif // MAINWINDOW_H
