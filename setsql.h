#ifndef GETURL_H
#define GETURL_H
#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <stdio.h>
#include <cstdlib>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <qtextcodec.h>

#include "coption.h"

class setsql
{
public:
    QString host;
    QString user;
    QString pasw;
    QString db;
    int sql;
    int is_must;
    QString mustStr;
    QString mustStr1;
    QString sleep_time;
    /*tags */
    QString *tag;
    QString *tagend;
    /*tables*/
    QString tableName;
    QString *table;

    setsql();

    bool setdb(void);
    QString runtimes(QString urlcode);
public slots:

protected:

private:
    volatile bool stopped;
    QSqlDatabase con;

};

#endif // GETURL_H
