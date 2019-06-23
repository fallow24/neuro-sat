#include "simulation.h"

Simulation::Simulation()
{
    this->sat = NULL;
    this->duration = 0;
}

Simulation::Simulation(Satellite* sat, double t)
{
    this->sat = sat;
    this->duration = t;
    this->steps = static_cast<long>(t / TIME_STEP);
}

Satellite * Simulation::getSatellite()
{
    return sat;
}

long Simulation::getSteps()
{
    return steps;
}

Simulation::~Simulation() {

}
