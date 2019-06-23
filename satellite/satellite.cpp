#include "satellite.h"

Vector3d Satellite::getRotSpeed()
{
    return rotSpeed;
}

vector<Wheel*> Satellite::getWheels()
{
    return wheels;
}

void Satellite::putWheel(Wheel * wheel)
{
    wheels.push_back(wheel);
}

void Satellite::putWheel(double mass, double radius, double maxRotSpeed, double maxTorque, Vector3d rotAxis)
{
    Wheel* wheel = new Wheel(mass, radius, maxRotSpeed, maxTorque, rotAxis);
    putWheel(wheel);
}

double Satellite::roll()
{
    return atan2(z.y(), z.z());
}

double Satellite::pitch()
{
    return atan2(-z.x(), sqrt(z.y()*z.y() + z.z()*z.z()));
}

double Satellite::yaw()
{
    return atan2(y.x(), x.x());
}

void Satellite::reset()
{
    t = 0;
    x = Vector3d(1, 0, 0);
    y = Vector3d(0, 1, 0);
    z = Vector3d(0, 0, 1);
    rotSpeed = Vector3d(0, 0, 0);
    for (int i = 0; i < wheels.size(); i++)
        wheels.at(i)->reset();
}

void Satellite::update(double dt) {
    t += dt;

    //L is the entire angular momentum of all reaction wheels
    Vector3d L(0, 0, 0);

    //I is the satellites moment of inertia
    Matrix3d I = this->getInertia();

    //sum up all the single angular momentums of each reaction wheel
    for(int i = 0; i < wheels.size(); i++)
        L += wheels.at(i)->angularMomentum();

    /*
     *Calculate the rotation speed w of the Satellite
     *L = I * w   ->   w = I⁻¹ * L
     *that is the same as solving the linear system for w
     */
    Vector3d w = I.colPivHouseholderQr().solve(L);

    //Disturbance
    w = disturb(w, t);

    //apply noise
    if (NOISY) rotSpeed = applyNoise(w);
    else rotSpeed = w;

    //apply the satellites rotation speed to its orientation
    Vector3d dx = rotSpeed * dt;
    rotateVecAround(&x, dx.x(), dx.y(), dx.z());
    rotateVecAround(&y, dx.x(), dx.y(), dx.z());
    rotateVecAround(&z, dx.x(), dx.y(), dx.z());

    //update the orientation of the reaction wheels
    for(int i = 0; i < wheels.size(); i++)
        wheels.at(i)->update(dx, dt);
}


