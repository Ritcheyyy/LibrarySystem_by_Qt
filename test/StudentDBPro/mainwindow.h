#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlTableModel>
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
    void studentTableOP();
    void setWinStyle();

private slots:
    void on_okBtn_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void editShowDialog();
private:
    Ui::MainWindow *ui;
    DBOperator DBO;
    QSqlTableModel *tm;
};
#endif // MAINWINDOW_H
