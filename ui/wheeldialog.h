#ifndef WHEELDIALOG_H
#define WHEELDIALOG_H

#include <QDialog>

namespace Ui {
class WheelDialog;
}

class WheelDialog : public QDialog
{
    Q_OBJECT

public:
    //explicit WheelDialog(QWidget *parent = nullptr);
    explicit WheelDialog(QWidget *parent = nullptr, double=0, double=0, double=0, double=0, double=0, double=0, double=0);
    ~WheelDialog();
    double mass, radius, maxSpeed, maxTorque, x, y, z;
    bool return_ok;


private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::WheelDialog *ui;

};

#endif // WHEELDIALOG_H
