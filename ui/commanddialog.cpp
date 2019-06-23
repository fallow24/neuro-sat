#include "commanddialog.h"
#include "ui_commanddialog.h"

CommandDialog::CommandDialog(QWidget *parent, double t, double x, double y, double z) :
    QDialog(parent),
    ui(new Ui::CommandDialog)
{
    ui->setupUi(this);
    ui->timeEdit->setText(QString("%1").arg(t));
    ui->xEdit->setText(QString("%1").arg(x));
    ui->yEdit->setText(QString("%1").arg(y));
    ui->zEdit->setText(QString("%1").arg(z));
    return_ok = false;
}

CommandDialog::~CommandDialog()
{
    delete ui;
}

void CommandDialog::on_cmdOk_clicked()
{
    t = ui->timeEdit->text().toDouble();
    x = ui->xEdit->text().toDouble();
    y = ui->yEdit->text().toDouble();
    z = ui->zEdit->text().toDouble();
    return_ok = true;
    this->close();
}

void CommandDialog::on_cmdCancel_clicked()
{
    return_ok = false;
    this->close();
}
