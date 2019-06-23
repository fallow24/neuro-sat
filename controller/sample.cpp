#include "sample.h"

Sample::Sample() {}

Sample::Sample(double dt, Vector3d dw, Vector3d u)
{
    this->dt = dt;
    this->dw = dw;
    this->u = u;
}

double Sample::t() {return dt;}
double Sample::ux() {return u.x();}
double Sample::uy() {return u.y();}
double Sample::uz() {return u.z();}
double Sample::dwx() {return dw.x();}
double Sample::dwy() {return dw.y();}
double Sample::dwz() {return dw.z();}
