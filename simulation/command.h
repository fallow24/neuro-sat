#ifndef COMMAND_H
#define COMMAND_H

#include "lib/Eigen/Dense"
#include "QMetaType"
using namespace Eigen;

class Command
{
private:
    double t;
    Vector3d desRotSpeed;

public:
    Command(double, Vector3d);
    double getTime();
    Vector3d getRotSpeed();
    Vector3d acceptIfReady(double, Vector3d);
};

Q_DECLARE_METATYPE(Command*)

#endif // COMMAND_H
