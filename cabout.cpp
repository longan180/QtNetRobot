#include "cabout.h"
#include "ui_cabout.h"

cabout::cabout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cabout)
{
    ui->setupUi(this);
    setWindowTitle(QString("About net Robot"));
    ui->textEdit->setReadOnly(true);
    ui->textEdit->append(QString("net Robot 0.2"));
    ui->textEdit->append(QString("\nBased on: longan@live.com"));
    ui->textEdit->append(QString("Copyright (C) 2008-2014 The chinalao developers\n"));
    ui->textEdit->append(QString("Qt %1 [built-with]").arg(qVersion()));
    ui->textEdit->append(QString("Qt %1 [running-with]").arg(QT_VERSION_STR));
}

cabout::~cabout()
{
    delete ui;
}

void cabout::on_pushButton_clicked()
{
    this->close();
}
