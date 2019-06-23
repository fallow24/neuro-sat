#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences(QWidget *parent, double scaling, double frequency, double percentage) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
    ui->in_scale->setText(QString("%1").arg(scaling));
    ui->dist_freq->setText(QString("%1").arg(frequency));
    ui->dist_perc->setText(QString("%1").arg(percentage));
    return_ok = false;
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::on_apply_clicked()
{
    m_scaling = ui->in_scale->text().toDouble();
    m_frequency = ui->dist_freq->text().toDouble();
    m_percentage = ui->dist_perc->text().toDouble();
    return_ok = true;
    this->close();
}

void Preferences::on_cancel_clicked()
{
    return_ok = false;
    this->close();
}
