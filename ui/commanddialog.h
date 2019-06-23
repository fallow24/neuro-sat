#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H

#include <QDialog>

namespace Ui {
class CommandDialog;
}

class CommandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommandDialog(QWidget *parent = nullptr, double t = 0, double x = 0, double y = 0, double z = 0);
    ~CommandDialog();
    bool return_ok;
    double t, x, y, z;

private slots:
    void on_cmdOk_clicked();

    void on_cmdCancel_clicked();

private:
    Ui::CommandDialog *ui;
};

#endif // COMMANDDIALOG_H
