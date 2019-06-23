#include "command.h"

Command::Command(double t, Vector3d desRotSpeed)
{
    this->t = t;
    this->desRotSpeed = desRotSpeed;
}

Vector3d Command::acceptIfReady(double t, Vector3d oldVal)
{
    if (fabs(this->t - t) < 0.01) return this->desRotSpeed;
    else return oldVal;
}

double Command::getTime()
{
    return t;
}

Vector3d Command::getRotSpeed()
{
    return desRotSpeed;
}
