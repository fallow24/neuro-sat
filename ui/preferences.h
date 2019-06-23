#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include "controller/samplegenerator.h" //For input scaling

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(QWidget *parent = nullptr, double scaling = INPUT_SCALING, double frequency = DISTURBANCE_FREQUENCY, double percentage = DISTURBANCE_PERCENTAGE);
    ~Preferences();
    double m_scaling;
    double m_frequency;
    double m_percentage;
    bool return_ok;

private slots:
    void on_apply_clicked();

    void on_cancel_clicked();

private:
    Ui::Preferences *ui;
};

#endif // PREFERENCES_H
