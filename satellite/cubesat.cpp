#include "cubesat.h"

CubeSat::CubeSat(double mass, double length)
{
    this->t = 0;
    this->mass = mass;
    this->length = length;
    this->rotSpeed = Vector3d(0,0,0);
}

Matrix3d CubeSat::getInertia() {
    double c = (mass / 6.0) * length * length;
    Matrix3d I;
    I << c, 0, 0,
         0, c, 0,
         0, 0, c;
    return I;
}
