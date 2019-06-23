#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#include "sample.h"
#include "satellitesimulation.h"
#include <QProgressBar>
#include <QObject>

#define SPEED_RANGE 0.1
#define TIME_RANGE 5
#define SIGNAL_RANGE 1
#define INPUT_SCALING 5000

#define DELIMITER ';'

using namespace std;

class SampleGenerator : public QObject
{

    Q_OBJECT

private:
    Satellite* sat;
    uniform_real_distribution<double> w_distr;
    uniform_real_distribution<double> t_distr;
    uniform_real_distribution<double> u_distr;
    default_random_engine rnd;
    bool m_stopped;
    double input_scaling;

public:
    SampleGenerator();
    SampleGenerator(Satellite*);
    void setSatellite(Satellite*);
    void setInputScaling(double);
    double getInputScaling();
    vector<Sample> generate(int);
    static void save(vector<Sample> &, const char *);
    static vector<Sample> load(const char *);

signals:
    void updated(int n);

public slots:
    void stopped();

};

#endif // SAMPLEGENERATOR_H
