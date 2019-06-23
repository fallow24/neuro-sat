#include "controller.h"

int Controller::getOutputSize()
{
    return this->outputSize;
}

void Controller::reset()
{
    lastTime = 0;
}
