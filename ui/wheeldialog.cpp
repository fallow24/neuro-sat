#include "wheeldialog.h"
#include "ui_wheeldialog.h"

/*
WheelDialog::WheelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WheelDialog)
{
    ui->setupUi(this);
    return_ok = false;
}
*/

WheelDialog::WheelDialog(QWidget *parent, double m, double r, double s, double t, double x, double y, double z)
    : QDialog (parent), ui(new Ui::WheelDialog)
{
    ui->setupUi(this);
    ui->massEdit->setText(QString("%1").arg(m));
    ui->radiusEdit->setText(QString("%1").arg(r));
    ui->speedEdit->setText(QString("%1").arg(s));
    ui->torqueEdit->setText(QString("%1").arg(t));
    ui->xEdit->setText(QString("%1").arg(x));
    ui->yEdit->setText(QString("%1").arg(y));
    ui->zEdit->setText(QString("%1").arg(z));
    return_ok = false;
}

WheelDialog::~WheelDialog()
{
    delete ui;
}

void WheelDialog::on_okButton_clicked()
{
    mass = ui->massEdit->text().toDouble();
    radius = ui->radiusEdit->text().toDouble();
    maxSpeed = ui->speedEdit->text().toDouble();
    maxTorque = ui->torqueEdit->text().toDouble();
    x = ui->xEdit->text().toDouble();
    y = ui->yEdit->text().toDouble();
    z = ui->zEdit->text().toDouble();
    return_ok = true;
    this->close();
}

void WheelDialog::on_cancelButton_clicked()
{
    return_ok = false;
    this->close();
}
