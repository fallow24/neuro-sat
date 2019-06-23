#include "wheel.h"

Wheel::Wheel(double mass, double radius, double maxRotSpeed, double maxTorque, Vector3d rotAxis)
{
    this->mass = mass;
    this->radius = radius;
    this->initRotAxis = rotAxis.normalized();
    this->rotAxis = rotAxis.normalized();
    this->torque = 0;
    this->rotSpeed = 0;
    this->maxTorque = maxTorque;
    this->maxRotSpeed = maxRotSpeed * 2 * M_PI * 1.0/60.0; //convert from cycles/min to rad/s
    this->inertia = 0.5 * mass * radius * radius;
    Kp = 0.0325; sample_time = 0.01; t = 0;
}

Vector3d Wheel::getAxis()
{
    return rotAxis;
}

/*
 * The angular momentum L is defined as the product of
 * the moment of inertia and the rotation speed, projected
 * on the e_x, e_y and e_z axes of the space-fixed frame
 */
Vector3d Wheel::angularMomentum()
{
    double L_abs = inertia * rotSpeed;
    double L_x = L_abs * rotAxis.x();
    double L_y = L_abs * rotAxis.y();
    double L_z = L_abs * rotAxis.z();
    return Vector3d(L_x, L_y, L_z);
}

//Activates Speed Mode, controlling to a reference speed of n * maxSpeed
void Wheel::speedModeControll(double n)
{
    CTRL_MODE = MODE_SPEED;
    if (n < -1) n = -1;
    else if (n > 1) n = 1;
    desRotSpeed = n * maxRotSpeed;
}

//Activates Torque Mode, controlling to a reference torque of n * maxTorque
void Wheel::torqueModeControll(double n)
{
    CTRL_MODE = MODE_TORQUE;
    if (n < -1) n = -1;
    else if (n > 1) n = 1;
    desTorque = n * maxTorque;
}

//Sets the rot speed percent instantly
void Wheel::setRotSpeed(double w)
{
    CTRL_MODE = MODE_SPEED;
    if (w < -1) w = -1;
    else if (w > 1) w = 1;
    desRotSpeed = w * maxRotSpeed;
    rotSpeed = desRotSpeed;
}

//Function that is called when operating in Torque Controll Mode
void Wheel::controllTorque(double dt)
{
    //Linear growth of torque
    if (desTorque > torque)
        torque += maxTorque / T_MAX_TORQUE * dt;
    else if (desTorque < torque)
        torque -= maxTorque / T_MAX_TORQUE * dt;

    //Bounds of torque (max and min (== -max))
    if (torque < -maxTorque) torque = -maxTorque;
    else if (torque > maxTorque) torque = maxTorque;
}

//Function that is called when operating in Speed Controll Mode
void Wheel::controllSpeed(double dt)
{
    //Using a simple P-Controller
    t += dt;
    if (sample_time >= t)
    {
        double err = desRotSpeed - rotSpeed;
        desTorque = Kp * err;
        if (desTorque < -maxTorque) desTorque = -maxTorque;
        else if (desTorque > maxTorque) desTorque = maxTorque;
        t = 0;
    }

    //Controll torque
    controllTorque(dt);
}

void Wheel::update(Vector3d w, double dt)
{
    //Determine controll mode + controll
    switch(CTRL_MODE)
    {
        case MODE_TORQUE:
            controllTorque(dt);
            break;
        case MODE_SPEED:
            controllSpeed(dt);
            break;
    }

    //update rotation speed:
    double a = torque / inertia; //acelleration
    rotSpeed += a * dt;
    if (rotSpeed > maxRotSpeed) rotSpeed = maxRotSpeed;
    else if (rotSpeed < -maxRotSpeed) rotSpeed = -maxRotSpeed;

    //update orientation of axis:
    rotateVecAround(&rotAxis, w.x(), w.y(), w.z());
}

void Wheel::reset()
{
    rotAxis = initRotAxis.normalized();
    rotSpeed = 0;
    torque = 0;
    desRotSpeed = 0;
    desTorque = 0;
}

double Wheel::getMass() { return mass; }

double Wheel::getRadius() { return radius; }

double Wheel::getMaxSpeed() { return maxRotSpeed; }

double Wheel::getMaxTorque() { return maxTorque; }




