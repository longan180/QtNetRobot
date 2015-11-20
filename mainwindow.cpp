#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boyermoore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString("net Robot Beta"));
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    ui->urlStat->setReadOnly(true);
    this->start_num = 0;

    /*network connect*/
    this->netManager = new QNetworkAccessManager(this);
    connect(this->netManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
    /*connect variable*/
    connect(this->ui->linkSetting, SIGNAL(clicked()), this, SLOT(linkSetting()));
    connect(this->ui->linkSetting, SIGNAL(clicked()), option, SLOT(linkoption()));
    /*test*/
//    this->ui->firstUrl->setText("http://weixin.sogou.com/pcindex/pc/pc_%1/pc_%1.html");
//    this->ui->firstNumber->setText("0");
//    this->ui->lastNumber->setText("0");
    /*times slot*/
    myTimer = new QTimer(this);

    connect(myTimer, SIGNAL(timeout()), this, SLOT(timerslot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    cabout *about = new cabout();
    about->setWindowModality(Qt::ApplicationModal);
    about->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionOption_triggered()
{
    option->setWindowModality(Qt::ApplicationModal);
    option->show();
}

void MainWindow::linkSetting()
{
    option->setWindowModality(Qt::ApplicationModal);
    option->show();
}

void MainWindow::on_linkstest_clicked()
{
    if(this->ui->firstUrl->text() == "" || this->ui->firstNumber->text() == "" || this->ui->lastNumber->text() == "") {
        QMessageBox::critical(NULL, "message", "error for textBox, contains empty text?", QMessageBox::Yes, QMessageBox::Yes);
    } else {
        QString first_url = this->ui->firstUrl->text();
        QString testlinkUrl;

        if(first_url.indexOf(QString("http://")) >= 0 || first_url.indexOf(QString("https://")) >= 0) {
            testlinkUrl = this->ui->firstUrl->text() + this->ui->firstNumber->text();
        } else {
            testlinkUrl = QString("http://") + this->ui->firstUrl->text() + this->ui->firstNumber->text();
        }
    }
}

void MainWindow::timerslot()
{
    //qDebug() << start_num;
    //qDebug() << all_urls;
    if(start_num <= all_urls) {
        QString linkUrl = (this->url_first.arg(QString::number(turls, 10)));
        qDebug() << linkUrl;
        QNetworkRequest req;
        req.setUrl(QUrl(linkUrl));
        req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        this->netManager->get(req);
        ++ turls;
        ++ start_num;
    } else {
        this->myTimer->stop();
        ui->start->setText("Start");
    }

}

void MainWindow::on_start_clicked()
{
    int isv = 1;
    for(int si = 0; si < 8; ++ si) {
        if((*(option->getTag() + si)) != "" && (*(option->getTable() + si)) == "") {
            isv = 0;
            QMessageBox::critical(NULL, "message", "error for setting, table not set?", QMessageBox::Yes, QMessageBox::Yes);
            option->show();
            break;
        }
    }

    if (option->getSql() == NULL || option->getUser() == NULL || option->getUser() == NULL || option->getPasw() == NULL|| option->getDb() == NULL) {
        QMessageBox::critical(NULL, "message", "error for setting, sql not set?", QMessageBox::Yes, QMessageBox::Yes);
        isv = 0;
        option->show();
    } else if( *(option->getTag()) == NULL || *(option->getTagend()) == NULL || *(option->getTable()) == NULL || option->getTableName() == NULL) {
        QMessageBox::critical(NULL, "message", "error for setting, sql not set?", QMessageBox::Yes, QMessageBox::Yes);
        isv = 0;
        option->show();
    }

    if(isv == 1){ //setting ok

        this->start_num = 0;
        this->url_first = this->ui->firstUrl->text();
        //this-> = this->ui->lastUrl->text();
        this->num_first = this->ui->firstNumber->text();
        this->num_last = this->ui->lastNumber->text();

        bool ok;
        all_urls = this->num_last.toInt(&ok, 10) - this->num_first.toInt(&ok, 10);
        turls = this->num_first.toInt(&ok, 10);
        lurls = this->num_last.toInt(&ok, 10);

        setsqls->sql = option->getSql();
        setsqls->host = option->getHost();
        setsqls->user = option->getUser();
        setsqls->pasw = option->getPasw();
        setsqls->db = option->getDb();

        setsqls->is_must = option->getIsMust();
        setsqls->mustStr = option->getMuststr();
        setsqls->mustStr1 = option->getMuststr1();

        setsqls->tag = option->getTag();
        setsqls->tagend = option->getTagend();
        setsqls->tableName = option->getTableName();
        setsqls->table = option->getTable();

        QString sleeptime = option->getSleep();

        int sptime;
        if(sleeptime == "") {
            sptime = 2000;
        } else {
            bool ok;
            sptime = sleeptime.toInt(&ok,10);
        }

        myTimer->setInterval(sptime);
        myTimer->setSingleShot(false);

        if ( this->myTimer->isActive() == true ) {
            this->myTimer->stop();
            ui->start->setText("Start");
        } else {
            this->myTimer->start();
            ui->start->setText("Stop");
        }
    }
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString t = codec->toUnicode((reply->readAll()));

    //qDebug() << t;
    QString codelist = setsqls->runtimes(t);
    qDebug() << codelist;
    if(codelist == "-2") {
        this->ui->urlStat->append("can't open sql odbc setting error?");
    } else if(codelist == "-1") {
        this->ui->urlStat->append("No data found,view url setting or must string");
    } else {
        this->ui->urlStat->append("finish!");
    }
}
