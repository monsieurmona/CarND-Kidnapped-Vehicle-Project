# Kidnapped Vehicle Project - Particle Filter
by Mario Lüder - Udacity's Self-Driving Car Nanodegree Program

## Overview

This repository contains all the code for the Localization course in Udacity's Self-Driving Car Nanodegree.

It implements a **Particle Filter**.

### Project Introduction
Your robot has been kidnapped and transported to a new location! Luckily it has a map of this location, a (noisy) GPS estimate of its initial location, and lots of (noisy) sensor and control data.

This project implements a 2 dimensional particle filter in C++. The particle filter has a map and some initial localization information (analogous to what a GPS would provide). At each time step the filter will also get observation and control data. (but no position anymore)

### Running the Code
This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)

This repository includes two files that can be used to set up and install uWebSocketIO for either Linux or Mac systems. For windows you can use either Docker, VMware, or even Windows 10 Bash on Ubuntu to install uWebSocketIO.

Once the install for uWebSocketIO is complete, the main program can be built and ran by doing the following from the project top directory.

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./particle_filter

Alternatively some scripts have been included to streamline this process, these can be leveraged by executing the following in the top directory of the project:

1. ./clean.sh
2. ./build.sh
3. ./run.sh

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

Here is the main protocol that main.cpp uses for uWebSocketIO in communicating with the simulator.

INPUT: values provided by the simulator to the c++ program

```
// sense noisy position data from the simulator
["sense_x"] ["sense_y"] ["sense_theta"]

// get the previous velocity and yaw rate to predict the particle's transitioned state
["previous_velocity"] ["previous_yawrate"]

// receive noisy observation data from the simulator, in a respective list of x/y values
["sense_observations_x"] ["sense_observations_y"]

OUTPUT: values provided by the c++ program to the simulator

// best particle values used for calculating the error evaluation
["best_particle_x"] ["best_particle_y"] ["best_particle_theta"]

//Optional message data used for debugging particle's sensing and associations

// for respective (x,y) sensed positions ID label
["best_particle_associations"]

// for respective (x,y) sensed positions
["best_particle_sense_x"] <= list of sensed x positions
["best_particle_sense_y"] <= list of sensed y positions
```

## Implementation the Particle Filter
The directory structure of this repository is as follows:

```
root
|   build.sh
|   clean.sh
|   CMakeLists.txt
|   README.md
|   run.sh
|
|___data
|   |   
|   |   map_data.txt
|   
|   
|___src
    |   Coordinate2D.hpp
    |   FixedSizeVector.hpp
    |   helper_functions.h
    |   json.hpp
    |   LandmarkAssociation.cpp
    |   LandmarkAssociation.hpp
    |   Landmark.cpp
    |   Landmark.hpp
    |   LandmarkMap.hpp
    |   Landmarks.hpp
    |   main.cpp
    |   MeanParticle.cpp
    |   MeanParticle.hpp
    |   MotionModel.cpp
    |   MotionModel.hpp
    |   Observations.hpp
    |   Particle.cpp
    |   ParticleFilter.cpp
    |   ParticleFilter.hpp
    |   Particle.hpp
    |   StandardDeviationLandmark.cpp
    |   StandardDeviationLandmark.hpp
    |   StandardDeviationPosition.cpp
    |   StandardDeviationPosition.hpp
```

The file `ParticleFilter.cpp` contains the methods for the filtering, while the other files contain classes for storrage and calculation.

The main filter uses memory that is known at compile time. There is no dynamic memory allocation except:
* the first initial allocation at program start to get the needed big arrays on the heap
* reading values from stream - positions and observations. (this part was written by udacity)
* Error debug messages output

The latter two must be replaced, if no dynamic memory should be used at all.

The class `FixedSizeVector` provides an array that can be used like a vector, but its internal capacity is fixed. The capacity must be know at compile time. If it is not created with new, the memory for the array is allocated on the stack. You may `push_back` or insert elements till no space is available anymore - the is now copy and reallocation.

### Inputs to the Particle Filter
You can find the inputs to the particle filter in the `data` directory.

#### The Map
`map_data.txt` includes the position of landmarks (in meters) on an arbitrary Cartesian coordinate system. Each row has three columns
1. x position
2. y position
3. landmark id