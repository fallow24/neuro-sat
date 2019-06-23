#ifndef TRAINWIZZARD_H
#define TRAINWIZZARD_H

#include "samplewizzard.h"
#include <QDialog>

namespace Ui {
class TrainWizzard;
}

class TrainWizzard : public QDialog
{
    Q_OBJECT

public:
    explicit TrainWizzard(QWidget *parent = nullptr, Satellite* sat = nullptr, double scaling = INPUT_SCALING);
    ~TrainWizzard();
    DNN * getDNN();
    bool return_ok;

private slots:
    void on_start_clicked();

    void on_cancel_clicked();

    void on_generate_clicked();

    void on_load_clicked();

private:
    Ui::TrainWizzard *ui;
    Satellite* sat;
    Progress* progress;
    QFuture<DNN*> ctrl;
    vector<Sample> samples;
    DNN *trainNetwork(Satellite* sat);
    int batchsize, epochs, layers, neurons, optIndex;
    double lrate;
    double scaling;
};

#endif // TRAINWIZZARD_H
