#ifndef CUBESAT_H
#define CUBESAT_H

#include "satellite.h"

class CubeSat : public Satellite
{

private:
    double mass, length; //kg, m

public:
    CubeSat(double, double);
    Matrix3d getInertia() override;

};

#endif // CUBESAT_H
