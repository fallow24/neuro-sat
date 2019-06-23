#include "dnn.h"

DNN::DNN() {
    this->input_scaling = INPUT_SCALING;
}

DNN::DNN(int hiddenlayers, int neurons, int outsize) : DNN()
{
    //net = new Network();
    this->hiddenLayers = hiddenlayers;
    this->neurons = neurons;
    this->outputSize = outsize;

    //Input Layer (4 inputs: dwx, dwy, dwz, dt)
    net.add_layer(new FullyConnected<Identity>(4, neurons));

    //Hidden layers
    for (int i = 0; i < hiddenLayers; i++)
        net.add_layer(new FullyConnected<Sigmoid>(neurons, neurons));

    //Network Output layer (3 outputs: ux, uy, uz)
    net.add_layer(new FullyConnected<Identity>(neurons, 3));
    net.set_output(new RegressionMSE());

    //Controller output (to the wheels)
    this->output = new double[outputSize];
    this->lastTime = 0;
}

DNN::DNN(Satellite* sat, int hiddenlayers, int neurons)
    : DNN(hiddenlayers, neurons, sat->getWheels().size()) {}

void DNN::setLRate(double a)
{
    opt->setLRate(a);
}

void DNN::setInputScaling(double c)
{
    this->input_scaling = c;
}

void DNN::setOptimizer(Optimizer * opt)
{
    this->opt = opt;
}

void DNN::train(vector<Sample> samples, int batchsize, int epoch)
{
    VerboseCallback call;
    net.set_callback(call);

    //Initialize network
    net.init(0, 0.01, 40);

    //Setup input and output data
    MatrixXd inputs(4, samples.size());
    MatrixXd outputs(3, samples.size());
    Sample s;
    for (int i = 0; i < samples.size(); i++)
    {
        s = samples[i];
        inputs.col(i) << s.t(), s.dwx(), s.dwy(), s.dwz();
        outputs.col(i) << s.ux(), s.uy(), s.uz();
    }

    //Actuall training of the network
    net.fit(*opt, inputs, outputs, batchsize, epoch, 40);
}

void DNN::save(const char * fileName)
{
    ofstream out(fileName);
    out << input_scaling << endl;
    out << hiddenLayers << endl;
    out << neurons << endl;
    out << outputSize << endl;
    vector<vector<double>> params = net.get_parameters();
    ostream_iterator<Scalar> output_iterator(out, " ");
    for (const auto& row : params) {
        copy(row.cbegin(), row.cend(), output_iterator);
        out << endl;
    }
}

Network * DNN::netPtr()
{
    return &this->net;
}

DNN * DNN::construct(const char * fileName)
{
    try {
        ifstream file(fileName);
        string line;

        getline(file, line);
        double c = QString(line.c_str()).toDouble();
        getline(file, line);
        int layers = stoi(line);
        getline(file, line);
        int neur = stoi(line);
        getline(file, line);
        int outsize = stoi(line);

        DNN * ctrl = new DNN(layers, neur, outsize);
        ctrl->setInputScaling(c);

        vector<vector<Scalar>> params = *(new vector<vector<Scalar>>());
        while (getline(file, line)) {
            stringstream linestream(line);
            string item;
            vector<Scalar> tmp = *(new vector<Scalar>());
            while (getline(linestream, item, ' ')) {
                QString qitem(item.c_str());
                tmp.push_back(qitem.toDouble());
            }
            params.push_back(tmp);
        }

        ctrl->net.init(0, 0.01, 40);
        ctrl->net.set_parameters(params);

        return ctrl;

    } catch (exception e) {
        throw ParseExcept();
    }

}

double * DNN::controll(Satellite * sat, Vector3d des_w, Vector3d w, double t)
{
    dt = t - lastTime;
    if (dt < SAMPLE_TIME) return output;
    else
    {
        //Calculate the Error
        Vector3d err = des_w - w;

        //Scale the error for network input
        Vector3d scaled_w = input_scaling * err / dt;

        //Feed input to the net, gather output
        MatrixXd input(4, 1);
        input.col(0) << dt, scaled_w.x(), scaled_w.y(), scaled_w.z();
        Vector3d u = net.predict(input);

        /*
         * The vector u stores the x-,y- and z-components that tell us
         * how to change the rotation speed on each axis. (X, Y and Z)
         * Now we calculate how much impact a reaction wheel will have on
         * that certain axis (using the dot product of the PIDs output 'u'
         * and the rotation axis of the wheel, which basically is a
         * weighted sum of both).
         */
        for(int i = 0; i < sat->getWheels().size(); i++) {
            //Rotation axis of wheel 'r'
            Vector3d r = sat->getWheels().at(i)->getAxis();
            double out =  u.dot(r);
            output[i] = out;
        }

        //Remember for next computation
        lastTime = t;

        return output;
    }
}
