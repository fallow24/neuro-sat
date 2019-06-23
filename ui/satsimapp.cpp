#include "satsimapp.h"
#include "ui_satsimapp.h"

SatSimApp::SatSimApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SatSimApp)
{
    ui->setupUi(this);
    scaling = INPUT_SCALING;

    //setup the graph
    ui->qPlot->addGraph();
    ui->qPlot->graph(0)->setPen(QPen(Qt::red));
    ui->qPlot->graph(0)->setName("w_x");
    ui->qPlot->addGraph();
    ui->qPlot->graph(1)->setPen(QPen(Qt::green));
    ui->qPlot->graph(1)->setName("w_y");
    ui->qPlot->addGraph();
    ui->qPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->qPlot->graph(2)->setName("w_z");
    ui->qPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->qPlot->legend->setFont(legendFont);
    ui->qPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
}

SatSimApp::~SatSimApp()
{
    delete ui;
}

void SatSimApp::on_startSimulation_clicked()
{
    ui->statusLabel->setText("simulating...");
    ui->statusLabel->repaint();

    //Get Satellite
    readSat();

    //Construct simulation (get controller)
    double duration = ui->durationEdit->text().toDouble();
    if (ui->ctrlTab->currentIndex() == 0)
        ctrl = new PID(sat, ui->pEdit->text().toDouble(), ui->iEdit->text().toDouble(), ui->dEdit->text().toDouble());
    else if (!netFile->isEmpty())
    {
        try {
            ctrl = DNN::construct(netFile->toLocal8Bit().data());
        } catch (ParseExcept pe) {
            QMessageBox::information(this, "Parse Exception", "The DNN file is corrupted.");
            ui->statusLabel->setText("");
            return;
        }
    }
    else {
        dnn->reset();
        ctrl = dnn;
    }

    try {
        simulation = new ControlledSim(sat, ctrl, duration);
    } catch (InvDimExcept ide) {
        QMessageBox::information(this, "Invalid Dimension Exception", "The selected controller is designed for a "
                                 + QString("%1").arg(ctrl->getOutputSize())
                                 + " wheel satellite.\nYou are using a satellite with "
                                 + QString("%1").arg(sat->getWheels().size())
                                 + " wheels!");
        ui->statusLabel->setText("");
        return;
    }

    //Get Commands
    for(int i = 0; i < ui->cmdComboBox->count(); i++)
    {
        simulation->putCommand(ui->cmdComboBox->itemData(i).value<Command*>());
    }

    //Run the simulation
    simulation->run();
    QMessageBox::information(this, "Simulation status", "Simulation finished!");
    ui->statusLabel->setText("");
    ui->statusLabel->repaint();

    //Draw the plot
    int n = simulation->getSteps();
    double *t_vals = simulation->t_values();
    double *wx_vals = simulation->wx_values();
    double *wy_vals = simulation->wy_values();
    double *wz_vals = simulation->wz_values();
    QVector<double> t(n), wx(n), wy(n), wz(n);
    for (int i = 0; i < n; i++)
    {
        t[i] = t_vals[i];
        wx[i] = wx_vals[i];
        wy[i] = wy_vals[i];
        wz[i] = wz_vals[i];
    }
    ui->qPlot->graph(0)->setData(t, wx);
    ui->qPlot->graph(1)->setData(t, wy);
    ui->qPlot->graph(2)->setData(t, wz);
    ui->qPlot->xAxis->setLabel("t /s");
    ui->qPlot->yAxis->setLabel("speed /rad/s");
    ui->qPlot->rescaleAxes();
    ui->qPlot->replot();

    //reset all wheels for later run
    for(int i = 0; i < ui->wheelComboBox->count(); i++)
    {
        ui->wheelComboBox->itemData(i).value<Wheel*>()->reset();
    }
}

void SatSimApp::on_addWheel_clicked()
{
    wheelDialog = new WheelDialog(this);
    wheelDialog->setWindowTitle("New Wheel");
    wheelDialog->setModal(true);
    wheelDialog->exec();

    if(wheelDialog->return_ok)
    {
        double m = wheelDialog->mass;
        double r = wheelDialog->radius;
        double s = wheelDialog->maxSpeed;
        double t = wheelDialog->maxTorque;
        double x = wheelDialog->x;
        double y = wheelDialog->y;
        double z = wheelDialog->z;
        Wheel * wheel = new Wheel(m,r,s,t,Vector3d(x,y,z));
        x = wheel->getAxis().x();
        y = wheel->getAxis().y();
        z = wheel->getAxis().z();
        QString str = QString("%1kg, %2m, %3rpm, %4Nm, [%5, %6, %7]").arg(m).arg(r).arg(s).arg(t).arg(x).arg(y).arg(z);
        ui->wheelComboBox->addItem(str, QVariant::fromValue(wheel));
    }
}

void SatSimApp::on_editWheel_clicked()
{
    Wheel * selected = ui->wheelComboBox->currentData().value<Wheel*>();
    if (selected == nullptr) return;
    double m = selected->getMass();
    double r = selected->getRadius();
    double s = (selected->getMaxSpeed() * 60.0) / (2 * M_PI);
    double t = selected->getMaxTorque();
    double x = selected->getAxis().x();
    double y = selected->getAxis().y();
    double z = selected->getAxis().z();
    wheelDialog = new WheelDialog(this,m,r,s,t,x,y,z);
    wheelDialog->setWindowTitle("Edit Wheel");
    wheelDialog->setModal(true);
    wheelDialog->exec();
    if(wheelDialog->return_ok)
    {
        ui->wheelComboBox->removeItem(ui->wheelComboBox->currentIndex());
        m = wheelDialog->mass;
        r = wheelDialog->radius;
        s = wheelDialog->maxSpeed;
        t = wheelDialog->maxTorque;
        x = wheelDialog->x;
        y = wheelDialog->y;
        z = wheelDialog->z;
        selected = new Wheel(m,r,s,t,Vector3d(x,y,z));
        x = selected->getAxis().x();
        y = selected->getAxis().y();
        z = selected->getAxis().z();
        QString str = QString("%1kg, %2m, %3rpm, %4Nm, [%5, %6, %7]").arg(m).arg(r).arg(s).arg(t).arg(x).arg(y).arg(z);
        ui->wheelComboBox->addItem(str, QVariant::fromValue(selected));
    }
}

void SatSimApp::on_removeWheel_clicked()
{
    ui->wheelComboBox->removeItem(ui->wheelComboBox->currentIndex());
}

void SatSimApp::on_addCmd_clicked()
{
    commandDialog = new CommandDialog(this);
    commandDialog->setWindowTitle("New Command");
    commandDialog->setModal(true);
    commandDialog->exec();
    if (commandDialog->return_ok)
    {
        double t = commandDialog->t;
        double x = commandDialog->x;
        double y = commandDialog->y;
        double z = commandDialog->z;
        Command* cmd = new Command(t, Vector3d(x,y,z));
        QString str = QString("%1s -> [%2, %3, %4]rad/s").arg(t).arg(x).arg(y).arg(z);
        ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
    }
}

void SatSimApp::on_editCmd_clicked()
{
    Command * cmd = ui->cmdComboBox->currentData().value<Command*>();
    if (cmd == nullptr) return;
    commandDialog = new CommandDialog(this, cmd->getTime(), cmd->getRotSpeed().x(), cmd->getRotSpeed().y(), cmd->getRotSpeed().z());
    commandDialog->setWindowTitle("Edit Command");
    commandDialog->setModal(true);
    commandDialog->exec();
    if (commandDialog->return_ok)
    {
        ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
        double t = commandDialog->t;
        double x = commandDialog->x;
        double y = commandDialog->y;
        double z = commandDialog->z;
        cmd = new Command(t, Vector3d(x,y,z));
        QString str = QString("%1s, [%2, %3, %4]rad/s").arg(t).arg(x).arg(y).arg(z);
        ui->cmdComboBox->addItem(str, QVariant::fromValue(cmd));
    }
}

void SatSimApp::on_removeCmd_clicked()
{
    ui->cmdComboBox->removeItem(ui->cmdComboBox->currentIndex());
}



void SatSimApp::on_exportDat_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export result of simulation"), "", tr("Data files (*.dat);;All Files (*)"));
    if (fileName.isEmpty()) return;
    ui->statusLabel->setText("saving...");
    ui->statusLabel->repaint();

    char * outFileName = fileName.toLocal8Bit().data();
    ofstream file;
    file.open(outFileName);
    file.clear();
    file << "t wx wy wz" << endl;

    double *t = simulation->t_values();
    double *wx = simulation->wx_values();
    double *wy = simulation->wy_values();
    double *wz = simulation->wz_values();
    for (int i = 0; i < simulation->getSteps(); i++)
    {
        file << t[i] << " " << wx[i] << " " << wy[i] << " " << wz[i] << endl;
    }
    ui->statusLabel->setText("");
}

void SatSimApp::on_actionRSI68_170_60_triggered()
{
    ui->wheelComboBox->clear();
    Wheel* w1 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(1, 0, 0));
    Wheel* w2 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(0, 1, 0));
    Wheel* w3 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(0, 0, 1));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [1, 0, 0]", QVariant::fromValue(w1));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [0, 1, 0]", QVariant::fromValue(w2));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [0, 0, 1]", QVariant::fromValue(w3));
}

void SatSimApp::on_action10Nms_Reaction_Wheel_triggered()
{
    ui->wheelComboBox->clear();
    Wheel* w1 = new Wheel(4.8, 0.1175, 5000, 0.21, Vector3d(0.707106781, 0.707106781, 0));
    Wheel* w2 = new Wheel(4.8, 0.1175, 5000, 0.21, Vector3d(0.40824829, -0.40824829, 0.816496581));
    Wheel* w3 = new Wheel(4.8, 0.1175, 5000, 0.21, Vector3d(-0.577350269, 0.577350269, 0.577350269));
    ui->wheelComboBox->addItem("4.8kg, 0.1175m, 5000rpm, 0.21Nm, [0.7, 0.7, 0]", QVariant::fromValue(w1));
    ui->wheelComboBox->addItem("4.8kg, 0.1175m, 5000rpm, 0.21Nm, [0.4, -0.4, 0.8]", QVariant::fromValue(w2));
    ui->wheelComboBox->addItem("4.8kg, 0.1175m, 5000rpm, 0.21Nm, [-0.5, 0.5, 0.5]", QVariant::fromValue(w3));
}

void SatSimApp::on_action4_Wheels_triggered()
{
    ui->wheelComboBox->clear();
    Wheel* w1 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(1, 1, 1));
    Wheel* w2 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(1, -1, 1));
    Wheel* w3 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(-1, 1, 1));
    Wheel* w4 = new Wheel(9.5, 0.347, 7300, 0.17, Vector3d(-1, -1, 1));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [1, 1, 1]", QVariant::fromValue(w1));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [1, -1, 1]", QVariant::fromValue(w2));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [-1, 1, 1]", QVariant::fromValue(w3));
    ui->wheelComboBox->addItem("9.5kg, 0.347m, 7300rpm, 0.17Nm, [-1, -1, 1]", QVariant::fromValue(w4));
}

void SatSimApp::on_actionFaulhaber_2209_triggered()
{
    ui->wheelComboBox->clear();
    Wheel* w1 = new Wheel(0.0097, 0.022, 10000, 0.00016, Vector3d(1, 0, 0));
    Wheel* w2 = new Wheel(0.0097, 0.022, 10000, 0.00016, Vector3d(0, 1, 0));
    Wheel* w3 = new Wheel(0.0097, 0.022, 10000, 0.00016, Vector3d(0, 0, 1));
    ui->wheelComboBox->addItem("9.7g, 22mm, 10000rpm, 0.16mNm, [1, 0, 0]", QVariant::fromValue(w1));
    ui->wheelComboBox->addItem("9.7g, 22mm, 10000rpm, 0.16mNm, [0, 1, 0]", QVariant::fromValue(w2));
    ui->wheelComboBox->addItem("9.7g, 22mm, 10000rpm, 0.16mNm, [0, 0, 1]", QVariant::fromValue(w3));
}

void SatSimApp::on_loadNet_clicked()
{
    netFile = new QString(QFileDialog::getOpenFileName(this, tr("Import network"), "", tr("DNN files (*.dnn);;All Files (*)")));
    if (netFile->isEmpty()) return;

    try { DNN::construct(netFile->toLocal8Bit().data()); }
    catch (ParseExcept pe) { QMessageBox::information(this, "Parse Warning", "The file was selected, but you will have problems running the simulation."); }

    char * netFileTmp = netFile->toLocal8Bit().data();
    QFileInfo fi(netFileTmp);
    ui->dnnStatus->setText(fi.fileName());
    ui->saveDnn->setEnabled(true);
}

void SatSimApp::on_train_clicked()
{
    readSat();
    trainWizzard = new TrainWizzard(this, sat, scaling);
    trainWizzard->setWindowTitle("DNN Training Wizzard");
    trainWizzard->setModal(true);
    trainWizzard->exec();

    if (trainWizzard->return_ok)
    {
        dnn = trainWizzard->getDNN();
        netFile = new QString("");
        ui->dnnStatus->setText("DNN Trained & ready!");
        ui->saveDnn->setEnabled(true);

    }

}

void SatSimApp::readSat() {
    if (ui->satTab->currentIndex() == 0) {
        double mass = ui->massEdit->text().toDouble();
        double length = ui->lengthEdit->text().toDouble();
        sat = new CubeSat(mass, length);
    } else {
        double x1,y1,z1,x2,y2,z2,x3,y3,z3;
        x1 = ui->x1->text().toDouble();
        x2 = ui->x2->text().toDouble();
        x3 = ui->x3->text().toDouble();
        y1 = ui->y1->text().toDouble();
        y2 = ui->y2->text().toDouble();
        y3 = ui->y3->text().toDouble();
        z1 = ui->z1->text().toDouble();
        z2 = ui->z2->text().toDouble();
        z3 = ui->z3->text().toDouble();
        sat = new ComplexSat(x1,y1,z1,x2,y2,z2,x3,y3,z3);
    }

    //Get Wheels
    for(int i = 0; i < ui->wheelComboBox->count(); i++)
    {
        sat->putWheel(ui->wheelComboBox->itemData(i).value<Wheel*>());
    }
}

void SatSimApp::on_saveDnn_clicked()
{
    QString qFileName = QFileDialog::getSaveFileName(this, tr("Import network"), "", tr("DNN files (*.dnn);;All Files (*)"));
    if (qFileName.isEmpty()) return;

    dnn->save(qFileName.toLocal8Bit().data());
}

void SatSimApp::on_actionPreferences_2_triggered()
{
    preferences = new Preferences(this, scaling, dist_freq, dist_perc);
    preferences->setWindowTitle("Preferences");
    preferences->setModal(true);
    preferences->exec();
    if (preferences->return_ok) {
        scaling = preferences->m_scaling;
        dist_freq = preferences->m_frequency;
        dist_perc = preferences->m_percentage;
    }
}
