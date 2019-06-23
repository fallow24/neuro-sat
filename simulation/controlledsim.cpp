#include "controlledsim.h"

ControlledSim::ControlledSim(Satellite* sat, Controller* ctrl, double t)
    : Simulation(sat, t)
{
    if (sat->getWheels().size() != ctrl->getOutputSize())
        throw InvDimExcept();

    this->ctrl = ctrl;
    this->sat = sat;
    this->t = new double[steps + 1];
    this->wx = new double[steps + 1];
    this->wy = new double[steps + 1];
    this->wz = new double[steps + 1];
}

//constructs a command, then adds it to the command list
void ControlledSim::putCommand(Command* cmd)
{
    commands.push_back(cmd);
}

void ControlledSim::run()
{
    //Simulation start
    int n = 0;
    for(double t = 0.0; t < duration; t+=TIME_STEP)
    {
        //Write status of sat in array
        this->t[n] = t;
        this->wx[n] = sat->getRotSpeed().x();
        this->wy[n] = sat->getRotSpeed().y();
        this->wz[n] = sat->getRotSpeed().z();
        n++;

        //search for a valid command
        for(int i = 0; i < commands.size(); i++)
            desired = commands.at(i)->acceptIfReady(t, desired);

        //Use the controller to predict the next output
        Vector3d present = sat->getRotSpeed();
        ctrl_out = ctrl->controll(sat, desired, present, t);

        //apply the controllers output to the reaction wheels
        for(int i = 0; i < sat->getWheels().size(); i++)
            sat->getWheels().at(i)->torqueModeControll(ctrl_out[i]);

        //update the satellite
        sat->update(TIME_STEP);

    }
}

double * ControlledSim::t_values() { return this->t; }

double * ControlledSim::wx_values() { return this->wx; }

double * ControlledSim::wy_values() { return this->wy; }

double * ControlledSim::wz_values() { return this->wz; }

ControlledSim::~ControlledSim() {}
