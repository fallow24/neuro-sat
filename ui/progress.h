#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QtConcurrent>
#include <QDebug>
#include "controller/dnn.h"
#include "controller/samplegenerator.h"
#include "utils.h"

#include "lib/MiniDNN/Network.h" //For training stopping

namespace Ui {
class Progress;
}

class Progress : public QDialog
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = nullptr);
    ~Progress();
    void setText(QString s);
    QPushButton * buttonPtr();
    QProgressBar *barPtr();

signals:
    void stopped(bool);

private slots:
    void on_stop_clicked();

private:
    Ui::Progress *ui;
};

#endif // PROGRESS_H
