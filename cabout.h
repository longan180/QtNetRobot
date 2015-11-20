#ifndef CABOUT_H
#define CABOUT_H

#include <QDialog>

namespace Ui {
class cabout;
}

class cabout : public QDialog
{
    Q_OBJECT

public:
    explicit cabout(QWidget *parent = 0);
    ~cabout();

private slots:
    void on_pushButton_clicked();

private:
    Ui::cabout *ui;
};

#endif // CABOUT_H
