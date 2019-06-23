#ifndef SATSIMAPP_H
#define SATSIMAPP_H

#include <QMainWindow>
#include <QFileDialog>
#include "satellitesimulation.h"
#include "wheeldialog.h"
#include "commanddialog.h"
#include "trainwizzard.h"
#include "progress.h"
#include "preferences.h"
#include "lib/MiniDNN/MiniDNN.h"
#include <iostream>
#include <fstream>

namespace Ui {
class SatSimApp;
}

class SatSimApp : public QMainWindow
{
    Q_OBJECT

//Simulation stuff comes right here
private:
    ControlledSim* simulation; //simulation pointer
    Controller * ctrl; //controller pointer
    DNN * dnn; //network pointer (if loadded)
    QString * netFile; //filename of loaded network
    Satellite* sat; //satellite pointer
    void readSat(); //reads satellite from gui
    double scaling; //input scaling for network

//UI stuff comes here
public:
    explicit SatSimApp(QWidget *parent = nullptr);
    ~SatSimApp();

private slots:
    void on_startSimulation_clicked();

    void on_addWheel_clicked();

    void on_editWheel_clicked();

    void on_removeWheel_clicked();

    void on_addCmd_clicked();

    void on_editCmd_clicked();

    void on_removeCmd_clicked();

    void on_exportDat_clicked();

    void on_actionRSI68_170_60_triggered();

    void on_action10Nms_Reaction_Wheel_triggered();

    void on_action4_Wheels_triggered();

    void on_actionFaulhaber_2209_triggered();

    void on_loadNet_clicked();

    void on_train_clicked();

    void on_saveDnn_clicked();

    void on_actionPreferences_2_triggered();

private:
    Ui::SatSimApp *ui;
    WheelDialog *wheelDialog;
    CommandDialog *commandDialog;
    TrainWizzard *trainWizzard;
    Progress *progress;
    Preferences *preferences;
};

#endif // SATSIMAPP_H
