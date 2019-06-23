#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progress)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
}


Progress::~Progress()
{
    delete ui;
}

void Progress::setText(QString s)
{
    ui->progressBar->setFormat(s);
}

QPushButton *Progress::buttonPtr()
{
    return ui->stop;
}

QProgressBar *Progress::barPtr()
{
    return ui->progressBar;
}

void Progress::on_stop_clicked()
{
    emit stopped(true);
    this->close();
}
