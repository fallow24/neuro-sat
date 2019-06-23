#include "samplewizzard.h"
#include "ui_samplewizzard.h"

SampleWizzard::SampleWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::SampleWizzard)
{
    ui->setupUi(this);
    this->sat = sat;
    return_ok = false;
    this->scaling = scaling;
}

SampleWizzard::~SampleWizzard()
{
    delete ui;
}

vector<Sample> SampleWizzard::getSamples()
{
    return samples.result();
}

vector<Sample> SampleWizzard::generateSamples(Satellite * sat, int n, double scaling)
{
    gen.setSatellite(sat);
    gen.setInputScaling(scaling);
    return gen.generate(n);
}

void SampleWizzard::saveSamples(QString &qFileName)
{
    while (samples.isRunning());
    vector<Sample> sampleVec = getSamples();
    SampleGenerator::save(sampleVec, qFileName.toLocal8Bit().data());
    return_ok = true;
    fileName = QString(qFileName);
    progress->close();
    this->close();
}

void SampleWizzard::on_generate_clicked()
{
    QString qFileName = QFileDialog::getSaveFileName(this, tr("Export samples"), "", tr("Tables (*.csv);;All Files (*)"));
    if (qFileName.isEmpty()) return;

    progress = new Progress(this);
    progress->setWindowTitle("Generating Samples Progress");
    progress->setModal(true);
    progress->setText("Generating Samples...");
    progress->show();

    int n = ui->number->text().toInt();

    //Connect the Samplegenerator to the Progressbar
    connect(&gen, &SampleGenerator::updated,
            progress->barPtr(), &QProgressBar::setValue);

    //Connect the Finish-Button to the SampleGenerator
    connect(progress, &Progress::stopped,
            &gen, &SampleGenerator::stopped);

    samples = QtConcurrent::run(this, &SampleWizzard::generateSamples, sat, n, scaling);
    QtConcurrent::run(this, &SampleWizzard::saveSamples, qFileName);
}
