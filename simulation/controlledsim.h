#ifndef CONTROLLEDSIM_H
#define CONTROLLEDSIM_H

#include "simulation.h"
#include "controller/controller.h"
#include "command.h"
#include "invdimexcept.h"

class ControlledSim : public Simulation
{
private:
    Controller * ctrl;
    double * ctrl_out;
    Vector3d desired;
    vector<Command*> commands;
    double * t; //t values
    double * wx; //rot speed on x axis values
    double * wy;
    double * wz;

public:
    ControlledSim(Satellite*, Controller*, double);
    void putCommand(Command*);
    double * t_values();
    double * wx_values();
    double * wy_values();
    double * wz_values();

    void run() override;
    ~ControlledSim() override;

};

#endif // CONTROLLEDSIM_H
