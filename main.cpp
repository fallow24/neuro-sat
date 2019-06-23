#include "ui/satsimapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    SatSimApp w;
    w.setFixedSize(w.size());
    w.show();

    std::cout << "This terminal is used for DNN training Callback. Do not close!" << std::endl;
    return a.exec();
}
