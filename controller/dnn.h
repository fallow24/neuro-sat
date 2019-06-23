#ifndef DNN_H
#define DNN_H

#include "sample.h"
#include "controller.h"
#include "samplegenerator.h" //for input scaling
#include "lib/MiniDNN/MiniDNN.h"

#include <QString>

#define CALLBACK_PRINT 1

using namespace MiniDNN;

class DNN : public Controller
{
private:
    Network net;
    Optimizer* opt;
    int hiddenLayers, neurons;
    double input_scaling;

public:
    DNN();
    DNN(int, int, int);
    DNN(Satellite*, int, int);
    Network * netPtr();
    void setLRate(double);
    void setInputScaling(double);
    void setOptimizer(Optimizer*);
    void train(vector<Sample>, int, int);
    double * controll(Satellite*, Vector3d, Vector3d, double) override;
    void save(const char *);
    static DNN * construct(const char *);

};

#endif // DNN_H
