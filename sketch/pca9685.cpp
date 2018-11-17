#include "pca9685.h"

PCA9685::PCA9685(TwoWire *bus, uint16_t addr) {
  i2cBus = bus;
  address = addr;
  // Initialize controller by default.
  init();
}

void PCA9685::init() {
  // Set controller to sleep.
  writeRegister(MODE1, 0x10);
  // Set calculated prescaler value.
  writeRegister(PRESCALE, getPrescaler());
  // Se controller to normal.
  writeRegister(MODE1, 0x00);
}

uint8_t PCA9685::getPrescaler() {
  // Update rate is number of PWM pulses in one second.
  double updateRate = 1000.0 / pwmCycle;
  return (uint8_t)((double)CLOCK_FREQ / PWM_STEPS / updateRate) - 1;
}

void PCA9685::writeRegister(uint8_t reg, uint8_t val) {
    i2cBus->beginTransmission((int)address);
    i2cBus->write(reg);
    i2cBus->write(val);
    i2cBus->endTransmission();
}

uint8_t PCA9685::readRegister(uint8_t reg) {
    i2cBus->beginTransmission((int)address);
    i2cBus->write(reg);
    i2cBus->endTransmission(false);
    i2cBus->requestFrom((uint8_t)address, (uint8_t)1);
    if (i2cBus->available() > 0) {
        return i2cBus->read();
    }
    return 0x00;
}

void PCA9685::setServo(uint8_t idx, double pw) {
  if (idx < MIN_LED_INDEX || idx > MAX_LED_INDEX) {
    return;
  }
  // https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
  uint16_t onSteps = (uint16_t)(((double)pwmDelay / pwmCycle) * PWM_STEPS);
  uint16_t offSteps = onSteps + (uint16_t)(((double)pw / pwmCycle) * PWM_STEPS);
  writeRegister(LED0_ON_L + 4 * idx, onSteps & 0xFF);
  writeRegister(LED0_ON_H + 4 * idx, (onSteps >> 8) & 0xFF);
  writeRegister(LED0_OFF_L + 4 * idx, offSteps & 0xFF);
  writeRegister(LED0_OFF_H + 4 * idx, (offSteps >> 8) & 0xFF);
}

