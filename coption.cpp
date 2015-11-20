#include "coption.h"
#include "ui_coption.h"
#include <QDebug>
coption::coption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::coption)
{
    ui->setupUi(this);
    setWindowTitle(QString("net Robot Settings"));
    // set ui
    this->ui->old_class1->setDisabled(true);
    this->ui->old_class2->setDisabled(true);
    this->ui->old_class3->setDisabled(true);
    this->ui->old_class4->setDisabled(true);
    this->ui->old_class5->setDisabled(true);
    this->ui->old_class6->setDisabled(true);
    this->ui->old_class7->setDisabled(true);
    this->ui->old_class8->setDisabled(true);
    this->ui->is_emdata->setChecked(true);
    //set option
    this->ui->optionTab->setCurrentIndex(0);
    //connect
    connect(this->ui->radioMysql, SIGNAL(clicked()), this, SLOT(click_radioMysql()));
    connect(this->ui->radioSqlite, SIGNAL(clicked()), this, SLOT(click_radioSqlite()));
    //set sqlite
    ui->radioSqlite->setChecked(true);
    this->sql = 0;
    this->click_radioSqlite();
    //test
//    this->ui->mysqlHost->setText("127.0.0.1");
//    this->ui->mysqlUser->setText("root");
//    this->ui->mysqlPasw->setText("bylong");
//    this->ui->mysqlDb->setText("test");

//    this->ui->tag1->setText("<p title=\"[\u0000-\uffff]{1,50}\"[>]");
//    this->ui->tage1->setText("</p>\\r\\n\\s*</a>\\r\\n\\s*<div class=\"fxf\">");
//    this->ui->tag2->setText("<h4><a uigs=\"pc_[\\0-9]{0,2}_tit_[\\0-9]{0,2}\" href=\"");
//    this->ui->tage2->setText("\" target=\"_blank\">[\u0000-\uffff]{1,50}</a></h4>");
//    this->ui->tag3->setText("<h4><a uigs=\"pc_[\\0-9]{0,2}_tit_[\\0-9]{0,2}\" href=\"[a-zA-z]+://[^\\s]*\" target=\"_blank\">");
//    this->ui->tage3->setText("</a></h4><a uigs=\"pc_[\\0-9]{0,2}_summary_[\\0-9]{0,2}\" href=\"");
    this->ui->sleep_time->setText("500");
//    this->ui->table_name->setText("urls");
//    this->ui->column1->setText("name");
//    this->ui->column2->setText("urls");
//    this->ui->column3->setText("title");
}

coption::~coption()
{
    delete ui;
}

void coption::on_opClose_clicked()
{
    this->close();
}

void coption::click_radioMysql()
{
    this->sql = 1;
    this->ui->mysqlDb->setDisabled(false);
    this->ui->mysqlHost->setDisabled(false);
    this->ui->mysqlPasw->setDisabled(false);
    this->ui->mysqlUser->setDisabled(false);
}

void coption::click_radioSqlite()
{
    this->sql = 2;
    //this->ui->mysqlDb->setDisabled(true);
    this->ui->mysqlHost->setDisabled(true);
    this->ui->mysqlPasw->setDisabled(true);
    this->ui->mysqlUser->setDisabled(true);
}

void coption::linkoption()
{
    this->ui->optionTab->setCurrentIndex(1);
}

QString coption::getHost(void)
{
    return this->myhost;
}

QString coption::getUser(void)
{
    return this->myuser;
}

QString coption::getPasw(void)
{
    return this->mypasw;
}

QString coption::getDb(void)
{
    return this->mydb;
}

int coption::getSql(void)
{
    return this->sql;
}

int coption::getIsMust()
{
    if(this->ui->is_must->isChecked()) {
        return 1;
    } else {
        return 2;
    }
}

QString coption::getMuststr(void)
{
    return this->mustStr;
}

QString coption::getMuststr1(void)
{
    return this->mustStr1;
}

QString coption::getSleep(void)
{
    return this->sleepTime;
}

QString *coption::getTag(void)
{
    return this->tag;
}

QString * coption::getTagend(void)
{
    return this->tagend;
}

QString coption::getTableName(void)
{
    return this->tableName;
}

QString *coption::getTable(void)
{
    return this->table;
}

void coption::on_opSave_clicked()
{
    if(this->ui->mysqlHost->text() != "") {
        this->myhost = this->ui->mysqlHost->text();
    }

    if(this->ui->mysqlUser->text() != "") {
        this->myuser = this->ui->mysqlUser->text();
    }

    if(this->ui->mysqlPasw->text() != "") {
      this->mypasw = this->ui->mysqlPasw->text();
    }

    if(this->ui->mysqlDb->text() != "") {
          this->mydb = this->ui->mysqlDb->text();
    }
    if(this->ui->musttext->text() != "") {
        this->mustStr = this->ui->musttext->text();
    }
    if(this->ui->musttext_2->text() != "") {
        this->mustStr1 = this->ui->musttext_2->text();
    }
    if(this->ui->table_name->text() != "") {
        this->tableName = this->ui->table_name->text();
    }

    if(this->ui->tag1->text() != "") {
        this->tag[0] = this->ui->tag1->text();
    }

    if(this->ui->tag2->text() != "") {
        this->tag[1] = this->ui->tag2->text();
    }

    if(this->ui->tag3->text() != "") {
        this->tag[2] = this->ui->tag3->text();
    }

    if(this->ui->tag4->text() != "") {
        this->tag[3] = this->ui->tag4->text();
    }

    if(this->ui->tag5->text() != "") {
        this->tag[4] = this->ui->tag5->text();
    }

    if(this->ui->tag6->text() != "") {
        this->tag[5] = this->ui->tag6->text();
    }

    if(this->ui->tag7->text() != "") {
        this->tag[6] = this->ui->tag7->text();
    }

    if(this->ui->tag8->text() != "") {
        this->tag[7] = this->ui->tag8->text();
    }

    if(this->ui->tage1->text() != "") {
        this->tagend[0] = this->ui->tage1->text();
    }

    if(this->ui->tage2->text() != "") {
        this->tagend[1] = this->ui->tage2->text();
    }

    if(this->ui->tage3->text() != "") {
        this->tagend[2] = this->ui->tage3->text();
    }

    if(this->ui->tage4->text() != "") {
        this->tagend[3] = this->ui->tage4->text();
    }

    if(this->ui->tage5->text() != "") {
        this->tagend[4] = this->ui->tage5->text();
    }

    if(this->ui->tage6->text() != "") {
        this->tagend[5] = this->ui->tage6->text();
    }

    if(this->ui->tage7->text() != "") {
        this->tagend[6] = this->ui->tage7->text();
    }

    if(this->ui->tage8->text() != "") {
        this->tagend[7] = this->ui->tage8->text();
    }

    if(this->ui->column1->text() != "") {
        this->table[0] = this->ui->column1->text();
    }
    if(this->ui->column2->text() != "") {
        this->table[1] = this->ui->column2->text();
    }
    if(this->ui->column3->text() != "") {
        this->table[2] = this->ui->column3->text();
    }
    if(this->ui->column4->text() != "") {
        this->table[3] = this->ui->column4->text();
    }
    if(this->ui->column5->text() != "") {
        this->table[4] = this->ui->column5->text();
    }
    if(this->ui->column6->text() != "") {
        this->table[5] = this->ui->column6->text();
    }
    if(this->ui->column7->text() != "") {
        this->table[6] = this->ui->column7->text();
    }
    if(this->ui->column8->text() != "") {
        this->table[7] = this->ui->column8->text();
    }
    if(this->ui->sleep_time->text() != "") {
        this->sleepTime = this->ui->sleep_time->text();
    }

    this->close();
}

void coption::on_optionTab_currentChanged(int index)
{
    this->ui->old_class1->setText(this->ui->tag1->text());
    this->ui->old_class2->setText(this->ui->tag2->text());
    this->ui->old_class3->setText(this->ui->tag3->text());
    this->ui->old_class4->setText(this->ui->tag4->text());
    this->ui->old_class5->setText(this->ui->tag5->text());
    this->ui->old_class6->setText(this->ui->tag6->text());
    this->ui->old_class7->setText(this->ui->tag7->text());
    this->ui->old_class8->setText(this->ui->tag8->text());
}

