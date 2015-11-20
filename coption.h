#ifndef COPTION_H
#define COPTION_H

#include <QDialog>

namespace Ui {
class coption;
}

class coption : public QDialog
{
    Q_OBJECT

public:
    Ui::coption *ui;

    QString myhost;
    QString myuser;
    QString mypasw;
    QString mydb;
    int sql;
    QString mustStr;
    QString mustStr1;
    QString sleepTime;
    /*tags */
    QString tag[8];
    QString tagend[8];
    /*tables*/
    QString tableName;
    QString table[8];

    /*public function*/
    QString getHost(void);
    QString getUser(void);
    QString getPasw(void);
    QString getDb(void);
    int getSql(void);
    int getIsemdate(void);
    int getIsMust(void);
    QString getTableName(void);
    QString getMuststr(void);
    QString getMuststr1(void);
    QString getSleep(void);
    QString *getTag(void);
    QString *getTagend(void);
    QString *getTable(void);


    explicit coption(QWidget *parent = 0);

    ~coption();

private slots:
    void on_opClose_clicked();

    void click_radioMysql();

    void click_radioSqlite();

    void linkoption();


    void on_opSave_clicked();

    void on_optionTab_currentChanged(int index);

private:

};

#endif // COPTION_H
