#include "complexsat.h"

ComplexSat::ComplexSat(Matrix3d inertia)
{
    this->t = 0;
    this->inertia = inertia;
    this->rotSpeed = Vector3d(0,0,0);
}

ComplexSat::ComplexSat(double x1, double y1, double z1,
                       double x2, double y2, double z2,
                       double x3, double y3, double z3)
{
    this->t = 0;
    Matrix3d I;
    I << x1, y1, z1,
         x2, y2, z2,
         x3, y3, z3;
    this->inertia = I;
    this->rotSpeed = Vector3d(0,0,0);
}

Matrix3d ComplexSat::getInertia()
{
    return inertia;
}
