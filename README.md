# Arduino-PCA9685

Arduino libraries + utility for servo control using PCA9685.

## Intro

This repository contains 3 main components:

1. A C++ library for Arduino to use PCA9685 to control servos.
1. A C++ library of servo profile to control servos using angles.
1. An interactive Arduino sketch tool using above two libraries.

## PCA9685 Library

This library provides a simple interface to communicate with PCA9685 servo controller board to control servos.

How to use this library:

1. Put [pca9685.h](sketch/pca9685.h) and [pca9685.cpp](sketch/pca9685.cpp) in your sketch folder.
1. In your sketch:
  ```c
  #include "pca9685.h"
  
  #define SDA       18                // I2C bus data pin on Arduino.
  #define SCL       19                // I2C bus clock pin on Arduino.
  #define I2C_ADDR  0x40              // The I2C address of your PCA9685.
  
  void setup() {
    // Initialze I2C with Wire.
    Wire.begin(SDA, SCL);
    
    // Initialize PCA9685 with Wire pointer and I2C address.
    PCA9685 pca9685(&Wire, I2C_ADDR);
    
    // This is the only API for PCA9685, it takes 2 parameters:
    // First parameter is the index of the servo: 0 ~ 14;
    // Second parameter is the pulse width in milliseconds.
    pca9685.setServo(0, 1.5);
  }
  ```
