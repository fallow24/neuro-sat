#include "instructedsim.h"

InstructedSim::InstructedSim(Satellite* sat, double t)
    :Simulation(sat, t) {}

void InstructedSim::setDuration(double t)
{
    this->duration = t;
}

void InstructedSim::putInstruction(double t, Wheel * wheel, double power)
{
    Instruction * instruction = new Instruction(t, wheel, power);
    instructions.push_back(instruction);
}

void InstructedSim::run()
{
    //Start of simulation
    for(double t = 0.0; t < duration; t += TIME_STEP)
    {
        //search for a valid instruction
        for(int i = 0; i < instructions.size(); i++)
            instructions.at(i)->execIfReady(t);

        //update the satellite
        sat->update(TIME_STEP);
     }
}

InstructedSim::~InstructedSim() {}

