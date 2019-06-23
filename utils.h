#ifndef UTILS_H
#define UTILS_H

#include <random>
#include "lib/Eigen/Dense"

#define DISTURBANCE_FREQUENCY 0.02 // HZ
#define DISTURBANCE_PERCENTAGE 0.01 //1%

static double dist_freq = DISTURBANCE_FREQUENCY;
static double dist_perc = DISTURBANCE_PERCENTAGE;

using namespace Eigen;

//Random Generator for noise
static std::uniform_real_distribution<double> unif(-0.001, 0.001);
static std::default_random_engine re;

//convert from degree to radians
#define deg2Rad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

//convert from radians to degree
#define rad2Deg(angleRadians) ((angleRadians) * 180.0 / M_PI)

//rotate a vector around roll pitch yaw with ZY'X'' convention
inline void rotateVecAround(Vector3d *vec, double roll, double pitch, double yaw) {
    Matrix3d rot;

    double cos_yaw = cos(yaw);
    double cos_pitch = cos(pitch);
    double cos_roll = cos(roll);

    double sin_yaw = sin(yaw);
    double sin_pitch = sin(pitch);
    double sin_roll = sin(roll);

    rot << cos_yaw*cos_pitch, cos_yaw*sin_pitch*sin_roll - sin_yaw*cos_roll, cos_yaw*sin_pitch*cos_roll + sin_yaw*sin_roll,
           sin_yaw*cos_pitch, sin_yaw*sin_pitch*sin_roll + cos_yaw*cos_roll, sin_yaw*sin_pitch*cos_roll - cos_yaw*sin_roll,
                -sin_pitch,                cos_pitch*sin_roll,                           cos_pitch*cos_roll;

    (*vec) = rot * (*vec);
}

inline Vector3d applyNoise(Vector3d w) {
    double noise_x = unif(re); //random number
    double noise_y = unif(re);
    double noise_z = unif(re);
    return w + Vector3d(noise_x * w.x(), noise_y * w.y(), noise_z * w.z());
}

inline Vector3d disturb(Vector3d w, double t) {
    double sin_t = sin(2 * M_PI * dist_freq * t);
    return w + dist_perc * Vector3d(w.x() * sin_t, w.y() * sin_t, w.z() * sin_t);
}

inline Vector3d round(Vector3d w)
{
    double wx = round(w.x() * 10000.0) / 10000.0;
    double wy = round(w.y() * 10000.0) / 10000.0;
    double wz = round(w.z() * 10000.0) / 10000.0;
    return Vector3d(wx, wy, wz);
}

#endif // UTILS_H
