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
     // first parameter is the index of the servo: 0 ~ 14;
     // second parameter is the servo pulse width in milliseconds.
     pca9685.setServo(0, 1.5);
   }
   ```

## Servo Profile Library

This library establishes a servo turning angle to pulse width profile for a specific servo. Under the hood, it takes in 3 calibration pulse widths at 0, 90 and 180 servo turning angle, and uses a second order curve to fit the 3 calibration points. When a desired turning angle is provided, it finds the pulse width using the fitted curve.

How to use this library:
1. Put [servoprofile.h](sketch/servoprofile.h) and [servoprofile.cpp](sketch/servoprofile.cpp) in your sketch folder.
1. In your sketch:
   ```c
   #include "servoprofile.h"
   
   void setup() {
     // Initialze a servo profile, which needs:
     // 0 degree turning angle reference servo pulse width;
     // 90 degree turning angle reference servo pulse width;
     // 180 degree turning angle reference servo pulse width.
     ServoProfile servo(0.6, 1.5, 2.4);
     
     // This is the only API of servo profile.
     // It computes the pulse width based on input turning angle,
     // and the 3 internal reference pulse widths.
     servo.computePulseWidth(45);
   }
   ```

## Utility


