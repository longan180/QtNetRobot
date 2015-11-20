#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <stdio.h>
#include <cstdlib>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <qtextcodec.h>

#include "cabout.h"
#include "coption.h"
#include "setsql.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    coption *option = new coption();
    QString url_first;
    QString url_last;
    QString num_first;
    QString num_last;

    ~MainWindow();

private slots:

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_actionOption_triggered();

    void linkSetting();

    void on_linkstest_clicked();

    void on_start_clicked();\

    void replyFinished(QNetworkReply *reply);

    void timerslot();

private:
    Ui::MainWindow *ui;

    setsql *setsqls = new setsql();
    QNetworkAccessManager *netManager;
    QString host;
    QString user;
    QString pasw;
    QString db;
    int sql;
    QString mustStr;
    QString mustStr1;
    int all_urls;
    int start_num;
    int turls;
    int lurls;

    QTimer* myTimer;
};

#endif // MAINWINDOW_H
