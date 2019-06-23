# neuro-sat

This is an application for simulating the rotation speed controll of any spacecraft either through PID or DNN controller using reaction wheels. The application is written in C++ and shipped with a QT graphical user interface:

![screenshot](https://user-images.githubusercontent.com/34287912/59918395-e5fff080-9424-11e9-8241-8583f9d19f41.png) 

The application is built on top of the [Eigen math library](http://eigen.tuxfamily.org/index.php?title=Main_Page) and the [MiniDNN](https://github.com/yixuan/MiniDNN) library for deep neural networks.  
However, you wont have to install those header-only libraries for yourself since they're shipped together with the neuro-wheels framework.

## Installation
