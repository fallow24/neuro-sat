# neuro-sat

This is an application for simulating the rotation speed controll of any spacecraft either through PID or DNN controller using reaction wheels. The application is written in C++ and shipped with a QT graphical user interface:

![screenshot](https://user-images.githubusercontent.com/34287912/59918395-e5fff080-9424-11e9-8241-8583f9d19f41.png) 

## Features:

 * Simulate any 3D spacecraft given its inertia and reaction wheels
 * Generate sample data, train deep neural networks and save / load them for later use
 * Add precession-disturbance to see if your controller can handle that
 * Compatible with Windows, MacOS and Linux
 * Free, light-weight and not heavy in resources

The application is built on top of the [Eigen math library](http://eigen.tuxfamily.org/index.php?title=Main_Page) and the [MiniDNN](https://github.com/yixuan/MiniDNN) library for deep neural networks.  
However, you wont have to install those header-only libraries for yourself since they're shipped together with the neuro-sat application.

## Installation

The installation requires you to have [qmake](https://doc.qt.io/qt-5/qmake-manual.html) installed.  
You can either have a version of [QT-creator](https://www.qt.io/download) installed, or get qmake independantly.  

Once you got that, installation is rather easy.
In your neuro-sat folder:

### Linux
  
```sh
mkdir build
cd build/
qmake ..
sudo make install
```

### MacOS

```sh
mkdir build
cd build/
qmake -spec macx-g++ ..
sudo make install
```

### Windows

 * Install [QT-creator](https://www.qt.io/download) (free & open source) 
 * Import the project using the _SatSimApp.pro_ file
 * Specify an output path and [create the .exe](https://stackoverflow.com/questions/25570752/how-to-make-exe-file-in-qt-creator) with building the project
