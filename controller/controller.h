#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "satellite/satellite.h"

#define SAMPLE_TIME 0.01

class Controller
{
protected:
    double dt, lastTime;
    double * output;
    int outputSize;

public:
    virtual double * controll(Satellite*, Vector3d, Vector3d, double) = 0;
    int getOutputSize();
    void reset();
};

#endif // CONTROLLER_H
