#include "pca9685.h"
#include "servoprofile.h"

#define SDA 18  // I2C data pin.
#define SCL 19  // I2C clock pin.
#define INPUT_SIZE 50 // Maximum input string length.
#define LED 0   // LED index

PCA9685 *pca9685;
ServoProfile *servo;

void setup() {
  // Initialize serial.
  Serial.begin(9600);
  Serial.println("");
  // Initialize PCA9685.
  Wire.begin(SDA, SCL);
  pca9685 = new PCA9685(&Wire, 0x40);
  // Initialize servo profile.
  servo = new ServoProfile();
}

char input[INPUT_SIZE + 1];
char command[INPUT_SIZE + 1];
char option[INPUT_SIZE + 1];
char value[INPUT_SIZE + 1];

void loop() {
  if (Serial.available() > 0) {
    uint16_t size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = '\0';
    char* field = strtok(input, ";");
    uint8_t idx = 0;
    while (field != 0) {
      if (idx == 0) {
        strncpy(command, field, INPUT_SIZE);
        Serial.println("Command: " + String(command));
      } else if (idx == 1) {
        strncpy(option, field, INPUT_SIZE);
        Serial.println("Option:  " + String(option));
      } else if (idx == 2) {
        strncpy(value, field, INPUT_SIZE);
        Serial.println("Value:   " + String(value));
        // Process.
        if (strcmp(command, "set") == 0) {
          if (strcmp(option, "pulse") == 0) {
            pca9685->setServo(LED, String(value).toFloat());
          } else if (strcmp(option, "angle") == 0) {
            pca9685->setServo(LED, servo->computePulseWidth(String(value).toFloat()));
          }
        } else if (strcmp(command, "save") == 0) {
          if (strcmp(option, "0") == 0) {
            servo->pulseWidth0 = String(value).toFloat();
          } else if (strcmp(option, "90") == 0) {
            servo->pulseWidth90 = String(value).toFloat();
          } else if (strcmp(option, "180") == 0) {
            servo->pulseWidth180 = String(value).toFloat();
          }
        }
      }
      field = strtok(0, ";");
      idx++;
    }
  }
}

