#ifndef PID_H
#define PID_H

#include "controller.h"

#define BOUND 1

#define KP_STD 30
#define TN_STD 5
#define TV_STD 0.04

class PID : public Controller
{

private:
    double Kp, Ki, Kd; //P, I, D
    double ux, uy, uz; //output of pid controller (3d)
    double Sx, Sy, Sz; //Components of integrator
    Vector3d lastErr; //used for calculation of dErr
    Vector3d lastSetpoint; //used for derivative of measurement

public:
    PID(Satellite *);
    PID(Satellite *, double, double, double);
    double * controll(Satellite*, Vector3d, Vector3d, double) override;
    void setTunings(double, double, double);

};

#endif // PID_H
