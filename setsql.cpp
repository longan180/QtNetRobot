#include "setsql.h"
#include <QDebug>
#include <QSqlError>
setsql::setsql()
{

    /*static variable*/
    this->stopped = false;
}

bool setsql::setdb()
{

    /*mysql connect*/
    if(this->sql == 1) {
        this->con = QSqlDatabase::addDatabase("QMYSQL");
        this->con.setHostName(this->host);
        this->con.setDatabaseName(this->db);
        this->con.setPort(3306);
        this->con.setUserName(this->user);
        this->con.setPassword(this->pasw);
        if(this->con.open()) {
            //table isexct
            QSqlQuery query(this->con);
            query.exec(QString("select TABLE_NAME from INFORMATION_SCHEMA.TABLES "
                               "where TABLE_NAME='%1';").arg(tableName));

            if(query.next()) {
                if(query.value(0).toString() == this->tableName)
                    return true;
            } else {
                return false;
            }
        } else {
            return false;
        }

    } else if(this->sql == 2) {
        this->con = QSqlDatabase::addDatabase("QSQLITE");
        QMessageBox::warning(NULL, ("error"), this->con.lastError().text());
        this->con.setDatabaseName(this->db);
        if(this->con.open()) {
            QSqlQuery query(this->con);
            //create table
            query.exec(QString("select count(*) from sqlite_master"
                               " where type='table' and name='%1';").arg(tableName));
            if(query.next()) {
                if(query.value(0).toInt() == 0) {
                    qDebug() << "CREATE TABLE";
                    QString iswhere;
                    for(int sqli = 0; sqli < 8; ++ sqli) {
                        if((*(this->table + sqli) != NULL && *(this->table + sqli + 1) != NULL)) {
                            iswhere = iswhere + "`" + *(this->table + sqli) +"` text DEFAULT NULL,";
                        } else if((*(this->table + sqli) != NULL && *(this->table + sqli + 1) == NULL)) {
                            iswhere = iswhere + "`" + *(this->table + sqli) +"` text DEFAULT NULL";
                        }
                    }

                    QString tables = "CREATE TABLE `" + this->tableName +"`"
                                     "(`id` INTEGER PRIMARY KEY AUTOINCREMENT,"+ iswhere +");";

                    qDebug() << tables;
                    query.exec(tables);
                }
            }
            return true;
        } else {
            return false;
        }
    }
}

QString setsql::runtimes(QString urlcode)
{
    QString startstrs = *(this->tag);

    //array
    int datatags;
    for(datatags = 0; datatags < 8; ++ datatags) {
        if((*(this->tag + datatags) == NULL) || (*(this->tag + datatags) == "")) {
            break;
        }
    }

    QRegExp var_start(startstrs);
    var_start.setPatternSyntax(QRegExp::RegExp2);

    int datanum = urlcode.count(var_start);
    QString data_all[datatags][datanum];
    //
    if(datatags == 0 || datanum == 0) {
        data_all[0][0] = "-1";
        return "-1";
    }

    if(!this->con.isOpen()) {
        if(this->setdb() == false) {
            //sql init error
            data_all[0][0] = "-2";
            return "-2";
        }
    }

    if(this->is_must == 1 && this->mustStr != "") {
        int is_have_must = urlcode.indexOf(mustStr);
        if(is_have_must <= 0) {
            data_all[0][0] = "-1";
            return "-1";
        }
    }


    if(this->is_must == 1 && this->mustStr1 != "") {
        int is_have_must1 = urlcode.indexOf(mustStr1);
        if(is_have_must1 <= 0) {
            data_all[0][0] = "-1";
            return "-1";
        }
    }


    for(int i = 0; i < datatags; ++ i) {
        if((*(this->tag + i) != NULL) && (*(this->tag + i) != "")) {
            //find str
            QString startstr = *(this->tag + i);
            QString endstr = *(this->tagend + i);
            //search static
            int start_lable1 = 0;
            int start_len = 0;
            int end_lable1 = 0;
            int end_next_len = 0;
            //search Exp
            for(int j = 0; j < datanum; ++ j) {
                //start char
                QRegExp startrx(startstr);
                QRegExp stoprx(endstr);
                startrx.setPatternSyntax(QRegExp::RegExp2);
                stoprx.setPatternSyntax(QRegExp::RegExp2);
                //QRegExp::setPatternSyntax(QRegExp::Wildcard);

                start_lable1 = startrx.indexIn(urlcode, start_lable1 + start_len);
                start_len = startrx.matchedLength();

                end_lable1 = stoprx.indexIn(urlcode, end_lable1 + end_next_len);
                end_next_len = stoprx.matchedLength();

                if(start_lable1 < end_lable1) {
                    int start_lables = start_lable1 + start_len;
                    int selestr = end_lable1 - start_lables;
                    data_all[i][j] = urlcode.mid(start_lables, selestr);

                    qDebug() << urlcode.mid(start_lables, end_lable1 - start_lables);
//                    qDebug() << start_lable1;
//                    qDebug() << end_lable1;
                } else {
                    data_all[i][j] = "0";
                }
            }
        }
    }

    if((this->con.open())) {
        QSqlQuery query(this->con);
        //query.exec("INSERT INTO nns(name, path) VALUES ('sadasdfasf','cxvcxv');");
        for(int sqli = 0; sqli < datanum; ++ sqli) {
            QString tables;
            QString iskey;
            QString isval;
            for(int lsqli = 0; lsqli < datatags; ++ lsqli) {
                if((*(this->table + lsqli) != NULL && data_all[0][0] != "0")) {
                    iskey = iskey + *(this->table + lsqli) + ",";
                    isval = isval + "'" + data_all[lsqli][sqli] + "',";
                }
            }
            iskey.remove((iskey.length() - 1), iskey.length());
            isval.remove((isval.length() - 1), isval.length());
            tables = "INSERT INTO " + this->tableName + " (" + iskey+ ") VALUES (" + isval + ")";
            qDebug() << tables;
            if(iskey == "" || isval == "") {
                return "-1";
            } else {
                query.exec(tables);
            }
        }
    }


    this->con.close();
        //qDebug() << data_all;
    return "1";
}
