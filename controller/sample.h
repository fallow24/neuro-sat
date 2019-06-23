#ifndef SAMPLE_H
#define SAMPLE_H

#include "lib/Eigen/Dense"

using namespace Eigen;

class Sample
{
private:
    Vector3d dw;
    Vector3d u;
    double dt;

public:
    Sample();
    Sample(double, Vector3d, Vector3d);
    double dwx();
    double dwy();
    double dwz();
    double ux();
    double uy();
    double uz();
    double t();

};

#endif // SAMPLE_H
