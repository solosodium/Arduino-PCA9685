#ifndef PCA9685_H
#define PCA9685_H

#include <Wire.h>

/**
 * A wrapper class for PCA9685 servo controller.
 * It takes a I2C bus (Wire) and an address, and writes pulse width
 * to servo at specified index.
 */
class PCA9685 {

private:
    
    // LED index range, total 16 LEDs.
    static const uint8_t MIN_LED_INDEX = 0;
    static const uint8_t MAX_LED_INDEX = 15;
    // PWM number of steps, which is 4096.
    static const uint16_t PWM_STEPS = 4096;
    // PCA9685 internal clock frequency, which is 25 MHz.
    static const long CLOCK_FREQ = 25000000;

    // Register addresses.
    static const uint8_t MODE1 =      0x00;
    static const uint8_t PRESCALE =   0xFE;
    static const uint8_t LED0_ON_L =  0x06;
    static const uint8_t LED0_ON_H =  0x07;
    static const uint8_t LED0_OFF_L = 0x08;
    static const uint8_t LED0_OFF_H = 0x09;
    
    // PWM cycle in miliseconds, which usually is 20 ms to 60 ms.
    static const uint8_t pwmCycle = 20;
    // PWM delay in miliseconds, which should be smaller than pwmCycle.
    static const uint8_t pwmDelay = 5;

    // Wire pointer.
    TwoWire *i2cBus;

    // PCA9685 I2C address.
    uint16_t address;

    // Initialize controller:
    // set to sleep, set prescale, set to normal.
    void init();

    // Calculate prescaler value:
    // https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
    uint8_t getPrescaler();

    // Write byte value to a register.
    void writeRegister(uint8_t reg, uint8_t val);

    // Read byte value from a register.
    uint8_t readRegister(uint8_t reg);

public:

    // Constructor takes &Wire and I2C address. 
    PCA9685(TwoWire *bus, uint16_t addr);

    // Set servo pulse width (miliseconds) at servo index.
    void setServo(uint8_t idx, double pw);
};

#endif

