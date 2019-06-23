#ifndef INSTRUCTEDSIM_H
#define INSTRUCTEDSIM_H

#include "simulation.h"
#include "instruction.h"

class InstructedSim : public Simulation
{

private:
    vector<Instruction*> instructions;

public:
    InstructedSim(Satellite*, double);
    void setDuration(double);
    void putInstruction(double, Wheel*, double);
    void run() override;
    ~InstructedSim() override;

};

#endif // INSTRUCTEDSIM_H
