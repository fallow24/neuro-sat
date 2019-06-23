#ifndef WHEEL_H
#define WHEEL_H

#include "utils.h"
#include "lib/Eigen/Dense"
using namespace Eigen;

#define T_MAX_TORQUE 0.5

#define MODE_SPEED 0
#define MODE_TORQUE 1

//For QT
#include "QMetaType"

class Wheel
{
private:
    Vector3d initRotAxis, rotAxis; //normalized
    double mass, radius; //kg, m
    double rotSpeed, maxRotSpeed, desRotSpeed; //rad/s
    double torque, maxTorque, desTorque; //Nm
    double inertia; //0.5 * m * r²
    void controllSpeed(double);
    void controllTorque(double);

    //Controller attributes
    double Kp, sample_time, t;
    int CTRL_MODE;

public:
    //Construcor: id, mass, radius, maxRotSpeed, maxTorque, rotAxis
    Wheel(double, double, double, double, Vector3d);
    double getMass();
    double getRadius();
    double getMaxSpeed();
    double getMaxTorque();
    Vector3d getAxis();
    Vector3d angularMomentum(); //inertia * speed
    void update(Vector3d, double);
    void reset();
    void setRotSpeed(double);
    void speedModeControll(double);
    void torqueModeControll(double);
};

//For QT
Q_DECLARE_METATYPE(Wheel*)

#endif // WHEEL_H
