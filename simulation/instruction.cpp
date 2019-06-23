#include "instruction.h"

Instruction::Instruction(double t, Wheel* wheel, double power)
{
    this->t = t;
    this->wheel = wheel;
    this->power = power;
}

void Instruction::execIfReady(double t)
{
    if(fabs(this->t - t) < 0.01) wheel->speedModeControll(power);
}

double Instruction::getTime()
{
    return t;
}

Wheel * Instruction::getWheel()
{
    return wheel;
}

double Instruction::getPower()
{
    return power;
}
