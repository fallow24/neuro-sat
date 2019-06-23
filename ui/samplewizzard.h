#ifndef SAMPLEWIZZARD_H
#define SAMPLEWIZZARD_H

#include <QDialog>
#include <QFileDialog>
#include <QtConcurrent>

#include "progress.h"
#include "controller/samplegenerator.h"

namespace Ui {
class SampleWizzard;
}

class SampleWizzard : public QDialog
{
    Q_OBJECT

public:
    explicit SampleWizzard(QWidget *parent = nullptr, Satellite *sat = nullptr, double scaling =INPUT_SCALING);
    ~SampleWizzard();
    vector<Sample> getSamples();
    bool return_ok;
    QString fileName;

private slots:
    void on_generate_clicked();

private:
    Ui::SampleWizzard *ui;
    vector<Sample> generateSamples(Satellite*, int, double);
    void saveSamples(QString&);
    SampleGenerator gen;
    Progress * progress;
    Satellite *sat;
    QFuture<vector<Sample>> samples;
    double scaling;
};

#endif // SAMPLEWIZZARD_H
