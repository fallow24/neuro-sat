#include "trainwizzard.h"
#include "ui_trainwizzard.h"

TrainWizzard::TrainWizzard(QWidget *parent, Satellite *sat, double scaling) :
    QDialog(parent),
    ui(new Ui::TrainWizzard)
{
    ui->setupUi(this);
    return_ok = false;
    this->scaling = scaling;
    this->sat = sat;
}

TrainWizzard::~TrainWizzard()
{
    delete ui;
}

DNN * TrainWizzard::getDNN()
{
    return ctrl.result();
}

DNN *TrainWizzard::trainNetwork(Satellite *sat)
{
    DNN *dnn = new DNN(sat, layers, neurons);

    //Connect the Network train process to the progress bar
    connect(dnn->netPtr(), &Network::updated,
            progress->barPtr(), &QProgressBar::setValue);

    //Construct the optimizer
    Optimizer * opt;
    if (optIndex == 0)
        opt = new RMSProp();
    else if (optIndex == 1)
        opt = new AdaGrad();
    else
        opt = new SGD();

    dnn->setOptimizer(opt);
    dnn->setLRate(lrate);
    dnn->train(samples, batchsize, epochs);

    return_ok = true;
    progress->close();
    this->close();
    return dnn;
}

void TrainWizzard::on_start_clicked()
{
    batchsize = ui->batch->text().toInt();
    epochs = ui->epoch->text().toInt();
    layers = ui->layers->text().toInt();
    neurons = ui->neurons->text().toInt();
    optIndex = ui->optimizer->currentIndex();
    lrate = ui->lrate->text().toDouble();
    return_ok = true;

    progress = new Progress(this);
    progress->setWindowTitle("Network Training Process");
    progress->setModal(true);
    progress->setText("Feeding the DNN...");
    progress->buttonPtr()->setEnabled(false);
    progress->show();

    ctrl = QtConcurrent::run(this, &TrainWizzard::trainNetwork, sat);

}

void TrainWizzard::on_cancel_clicked()
{
    this->close();
}

void TrainWizzard::on_generate_clicked()
{
    SampleWizzard* sampleWizzard = new SampleWizzard(this, sat, scaling);
    sampleWizzard->setWindowTitle("Sample Generator");
    sampleWizzard->setModal(true);
    sampleWizzard->exec();

    if (sampleWizzard->return_ok) {
        samples = sampleWizzard->getSamples();
        QFileInfo fi(sampleWizzard->fileName);
        ui->samplesStatus->setText(fi.fileName() + " loaded.");
    }
}

void TrainWizzard::on_load_clicked()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Import samples"), "", tr("Tables (*.csv);;All Files (*)"));
    if (qFileName.isEmpty()) return;

    samples = SampleGenerator::load(qFileName.toLocal8Bit().data());
    QFileInfo fi(qFileName);
    ui->samplesStatus->setText(fi.fileName() + " loaded.");
}
