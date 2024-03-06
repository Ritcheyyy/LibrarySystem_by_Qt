#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QSqlQuery>
#include <string>
#include <QStackedWidget>
#include "first_window_for_visitor.h"
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_register_2_clicked();

    void on_login_clicked();


    void on_visitorLogin_clicked();

private:
    Ui::MainWindow *ui;
    first_window_for_visitor *fv;
    loginwindow *lw;
    registerwindow* re;
    QStackedWidget *sw;
};
#endif // MAINWINDOW_H
