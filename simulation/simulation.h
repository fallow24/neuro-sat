#ifndef SIMULATION_H
#define SIMULATION_H

#include "satellite/satellite.h"
#include <iostream>
#include <fstream>

#define TIME_STEP 0.001

class Simulation
{

protected:
    Satellite *sat;
    double duration;
    long steps; //number of simulation steps

public:
    virtual void run() = 0;

    Simulation();
    Simulation(Satellite*, double);
    long getSteps();
    Satellite* getSatellite();

    virtual ~Simulation();
};

#endif // SIMULATION_H
