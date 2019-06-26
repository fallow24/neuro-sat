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

### Linux and MacOS
  
```sh
mkdir build
cd build/
qmake ..
make
```

#### Problems on Linux

If you run into  
*QT: nothing to be done for ''*  
try  

```sh
sudo apt-get install qt5-default
```

#### Problems on MacOS

You might find youself not to be able to perform _make_.  
If that's the case, try installing XCode (from the appstore) & XCode Command Line Tools, as described in [this](https://stackoverflow.com/questions/9329243/xcode-install-command-line-tools) post.

### Windows

 * Install [QT-creator](https://www.qt.io/download) (free & open source) 
 * Import the project using the _SatSimApp.pro_ file
 * Specify an output path and [create the .exe](https://stackoverflow.com/questions/25570752/how-to-make-exe-file-in-qt-creator) with building the project
 
 ## First steps
 
 *Important note*: You can not expect a beautifull behaivior for _every_ setup of satellite + wheels + controller.  
 You will most likely run into a situation where some parameters have to be tuned in order for the controller to run perfectly smooth - or you will encounter a situation where the setup of satellite + wheels will not allow the controller to produce good results at all.  
 
 *For example: Speed saturation.*  
You might have a massive satellite but only give it tiny wheels. Probably this setup will not be able to spin any faster than 0.001 radians per second, so you might run into some strange behaivior if trying to speed up to more than that.

### Your first DNN Satellite attitude controller

In the menubar you can find some predefined *Wheel Samples*.
 * Start off with the *4 Wheels* setup, which is a pyramid-like arrangement of the [RSI68-170/60](https://www.rockwellcollins.com/Products-and-Services/Defense/Platforms/Space/High-Motor-Torque-Momentum-and-Reaction-Wheels.aspx) reaction wheel  
 * Construct a *Cubesat* with *mass 400kg* and *length 1m*  
 * Select *Neural network*, then *Train* a new one
 * In the *Sample generator* you have to create some training samples for the DNN to learn from. Create *1000 samples* and save them wherever you like
 * The next step may vary and is highly dependable on which setup you're using. You may find youself playing around with those values to get a good result. For the current setup, *batchsize 50*, *5000 epoches*, *1 hidden layer*, *50 neurons per hidden layer*, *RMSProp optimizer* and *0.0007 learning rate* works perfectly well
 * Start the training process and wait. The more power your machine has, the fewer time you will have to wait
 * Now you might want to *save* your trained network, so you might *load* it later
 * Add a new command to look at the 3D step-response that your network is able to perform. Keep *speed saturation* in mind! For this setup, speed values between *-0.04* to *0.04* rad/s should work fine
 * *Start the simulation.* Congrats! You (probably) just trained your first spacecraft attitude-controlling neural network

### Keep in mind

 * If you find yourself in that situation where you get great oszilations (or similar unexcpected behaivior) and can't get the controller to work properly, then most likely the satellite+wheel setup you're using is just poorly chosen.  
 * Adjusting the control setup is all about fine-tuning. A PID controller might perform superbad with some values but without any uncertainty with other ones. Also, getting a DNN to work just as good (or even better) than a PID controller is not an easy task. Keep your eyes open for *overfitting* or *too small sample sizes* and fiddle around with the other parameters until you find a good solution.
 
## About the author

This application is part of my bachelors thesis about _learning attitude control and simulation for spacecrafts_.  
If you want to find out more about how this simulator works (or how to get a neural network to replace a PID controller in a closed loop), get involved into the project or just ask something else:  
Feel free to [create an issue](https://github.com/fallow24/neuro-sat/issues)!

