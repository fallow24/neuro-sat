#ifndef COMPLEXSAT_H
#define COMPLEXSAT_H

#include "satellite.h"

class ComplexSat : public Satellite
{
private:
    Matrix3d inertia;

public:
    ComplexSat(Matrix3d inertia);
    ComplexSat(double, double, double, double, double, double, double, double, double);
    Matrix3d getInertia() override;

};

#endif // COMPLEXSAT_H
