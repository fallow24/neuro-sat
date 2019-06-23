#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "satellite/wheel.h"

class Instruction
{
private:
    double t;
    Wheel* wheel;
    double power;

public:
    Instruction(double, Wheel*, double);
    double getTime();
    Wheel * getWheel();
    double getPower();
    void execIfReady(double);
};

#endif // INSTRUCTION_H
