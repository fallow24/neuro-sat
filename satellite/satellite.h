#ifndef SATELLITE_H
#define SATELLITE_H

#include "wheel.h"
#include <vector>
using namespace std;

#define NOISY true

class Satellite
{

protected:
    vector<Wheel*> wheels; //list of all the wheels
    Vector3d x, y, z; //orientation vectors of the satellite
    Vector3d rotSpeed; //rotation speed of the satellite
    double t;

public:
    virtual Matrix3d getInertia() = 0;

    Vector3d getRotSpeed();
    vector<Wheel*> getWheels();
    void putWheel(Wheel*);
    void putWheel(double, double, double, double, Vector3d);
    double roll();
    double pitch();
    double yaw();
    void reset();
    void update(double);

};

#endif // SATELLITE_H
