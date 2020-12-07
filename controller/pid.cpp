#include "pid.h"

PID::PID(Satellite * sat) : Controller()
{
    Kp = KP_STD; Ki = TN_STD; Kd = TV_STD;
    Sx = 0; Sy = 0; Sz = 0;
    this->outputSize = sat->getWheels().size();
    this->output = new double[outputSize];
    lastErr = Vector3d(0,0,0);
}

PID::PID(Satellite* sat, double Kp, double Ki, double Kd)
    : PID(sat) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

double * PID::controll(Satellite* sat, Vector3d des_w, Vector3d w, double t)
{
    dt = t - lastTime;
    if (dt < SAMPLE_TIME) return output;

    else
    {
        //Calc error
        Vector3d err = des_w - w;

        //Calc integral, watch out for limits, do anti windup
        if (Ki == 0.0) { Sx = 0; Sy = 0; Sz = 0; }
        else
        {
            if (-BOUND < ux && ux < BOUND)
                Sx += Ki * err.x() * dt; if (Sx < -BOUND) Sx = -BOUND; if(BOUND < Sx) Sx = BOUND;
            if (-BOUND < uy && uy < BOUND)
                Sy += Ki * err.y() * dt; if (Sy < -BOUND) Sy = -BOUND; if(BOUND < Sy) Sy = BOUND;
            if (-BOUND < uz && uz < BOUND)
                Sz += Ki * err.z() * dt; if (Sz < -BOUND) Sz = -BOUND; if(BOUND < Sz) Sz = BOUND;
        }

        //Calc "Derivative of Measurement" (lose derivative kick)
        Vector3d dErr = (des_w - lastSetpoint) * (1.0 / dt) - (err - lastErr) * (1.0 / dt);

        //Calc u = P (err + I * S err dt + D * derr / dt)
        ux = Kp * err.x() + Sx + Kd * dErr.x();
        uy = Kp * err.y() + Sy + Kd * dErr.y();
        uz = Kp * err.z() + Sz + Kd * dErr.z();
        //adjusting output to the bounds
        if (ux < -BOUND) ux = -BOUND; if(BOUND < ux) ux = BOUND;
        if (uy < -BOUND) uy = -BOUND; if(BOUND < uy) uy = BOUND;
        if (uz < -BOUND) uz = -BOUND; if(BOUND < uz) uz = BOUND;
        Vector3d u(ux, uy, uz);

        /*
         * The vector u stores the x-,y- and z-components that tell us
         * how to change the rotation speed on each axis. (X, Y and Z)
         * Now we calculate how much impact a reaction wheel will have on
         * that certain axis (using the dot product of the PIDs output 'u'
         * and the rotation axis of the wheel, which basically is a
         * weighted sum of both).
         */
        for(unsigned long i = 0; i < sat->getWheels().size(); i++)
        {
            //Rotation axis of wheel 'r'
            Vector3d r = sat->getWheels().at(i)->getAxis();
            double out = u.dot(r);
            output[i] = out;
        }

        //Remember for next computation
        lastErr = err;
        lastTime = t;
        lastSetpoint = des_w;
        return output;
    }
}
