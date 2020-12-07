#include "samplegenerator.h"

SampleGenerator::SampleGenerator()
{
    w_distr = uniform_real_distribution<double>(-SPEED_RANGE, SPEED_RANGE);
    t_distr = uniform_real_distribution<double>(0.05, TIME_RANGE);
    u_distr = uniform_real_distribution<double>(-SIGNAL_RANGE, SIGNAL_RANGE);
    m_stopped = false;
    input_scaling = INPUT_SCALING;
}

SampleGenerator::SampleGenerator(Satellite* sat)
    : SampleGenerator()
{
    setSatellite(sat);
}

void SampleGenerator::setSatellite(Satellite * sat) {
    this->sat = sat;
}

void SampleGenerator::setInputScaling(double c)
{
    this->input_scaling = c;
}

double SampleGenerator::getInputScaling()
{
    return input_scaling;
}

//Generate a set of n samples
vector<Sample> SampleGenerator::generate(int nSamples)
{
    vector<Sample> samples = *(new vector<Sample>());

    double dt;
    InstructedSim sim(sat, 0);

    for (int n = 0; n < nSamples; n++)
    {
        //Threaded stuff:
        if (m_stopped) break;
        emit updated((double)n / nSamples * 100.0);

        //Generate random time intervall
        //dt = SAMPLE_TIME;
        dt = round(t_distr(rnd) * 1000.0) / 1000.0;
        sim.setDuration(dt);

        //Generate random controll output
        double ux = round(u_distr(rnd) * 1000.0) / 1000.0;
        double uy = round(u_distr(rnd) * 1000.0) / 1000.0;
        double uz = round(u_distr(rnd) * 1000.0) / 1000.0;

        //30 Percent of the data should be only 1 axis
        if (n >= 10) {
            if ((n - 1) % (int)(n / 10) == 0)       { ux = 0; uy = 0; }
            else if (n % (int)(n / 10) == 0)        { uy = 0; uz = 0; }
            else if ((n + 1) % (int)(n / 10) == 0)  { uz = 0; ux = 0; }
        }

        Vector3d u(ux, uy, uz);

        //Apply the controll output to the wheels
        for(int i = 0; i < sat->getWheels().size(); i++) {
            //Rotation axis of wheel 'r'
            Vector3d r = sat->getWheels().at(i)->getAxis();
            sat->getWheels().at(i)->torqueModeControll(u.dot(r));
        }

        //Run the simulation
        sim.run();
        //Compute dw
        Vector3d dw = sat->getRotSpeed() / dt;
        //Create new sample
        samples.push_back(*(new Sample(dt, round(input_scaling * dw), u)));
        //Reset the satellite for next simulation
        sat->reset();
    }

    //Samples where no controll output is used, add another 4% of data
    for (int i = 0; i < 4 * nSamples / 100; i++)
    {
        //Generate 0 controller output
        Vector3d u(0,0,0);

        //Apply the controll output to the wheels
        for(int i = 0; i < sat->getWheels().size(); i++) {
            //Rotation axis of wheel 'r'
            Vector3d r = sat->getWheels().at(i)->getAxis();
            sat->getWheels().at(i)->torqueModeControll(u.dot(r));
        }

        //Random time intervall
        dt = round(t_distr(rnd) * 1000.0) / 1000.0;
        sim.setDuration(dt);

        //Run the simulation
        sim.run();
        //Compute dw
        Vector3d dw = sat->getRotSpeed() / dt;
        //Create new sample
        samples.push_back(*(new Sample(dt, round(input_scaling * dw), u)));
        //Reset the satellite for next simulation
        sat->reset();
    }

    m_stopped = false;
    emit updated(100);

    return samples;
}

//Save samples to a file
void SampleGenerator::save(vector<Sample> &samples, const char * fileName)
{
    ofstream out(fileName);
    Sample s;
    for (int i = 0; i < samples.size(); i++)
    {
        s = samples.at(i);
        out << s.t() << DELIMITER << s.dwx() << DELIMITER << s.dwy() << DELIMITER << s.dwz() << DELIMITER
            << s.ux() << DELIMITER << s.uy() << DELIMITER << s.uz() << endl;
    }
    out.flush();
}

//Load a set of samples from a file
vector<Sample> SampleGenerator::load(const char * fileName)
{
    vector<Sample> samples = *(new vector<Sample>());

    //setup file
    ifstream file(fileName);
    string line;

    //Iterate lines
    while(getline(file, line)) {
        stringstream linestr(line);
        string item;

        //Read dt
        getline(linestr, item, ';');
        double dt = QString(item.c_str()).toDouble();

        //Read dw
        getline(linestr, item, ';');
        double dwx = QString(item.c_str()).toDouble();
        getline(linestr, item, ';');
        double dwy = QString(item.c_str()).toDouble();
        getline(linestr, item, ';');
        double dwz = QString(item.c_str()).toDouble();

        //Read u
        getline(linestr, item, ';');
        double ux = QString(item.c_str()).toDouble();
        getline(linestr, item, ';');
        double uy = QString(item.c_str()).toDouble();
        getline(linestr, item, ';');
        double uz = QString(item.c_str()).toDouble();

        //Push sample
        Vector3d dw(dwx, dwy, dwz);
        Vector3d u(ux, uy, uz);
        samples.push_back(*(new Sample(dt, dw, u)));
    }

    return samples;
}

void SampleGenerator::stopped()
{
    m_stopped = true;
}



