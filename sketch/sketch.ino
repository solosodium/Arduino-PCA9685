#include "pca9685.h"
#include "servoprofile.h"

/***** Configurations *****/

#define SDA         18      // I2C data pin.
#define SCL         19      // I2C clock pin.
#define I2C_ADDR    0x40    // I2C address.
#define SERVO_INDEX 0       // Servo index on PCA9685.
#define BAUD_RATE   115200  // Serial baud rate.
#define INPUT_SIZE  128     // Maximum input string length.

/***** Global variables *****/

// PCA9685 controller handle.
PCA9685 pca9685(&Wire, I2C_ADDR);

// Servo angle-pulse width profile.
ServoProfile servo(0.6, 1.5, 2.4);

// Serial input buffer.
char input[INPUT_SIZE];

/***** Setup *****/

void setup() {
  // Initialize serial.
  Serial.begin(BAUD_RATE);
  // Initialize Wire.
  Wire.begin(SDA, SCL);
  // Print welcome message.
  printWelcome();
  // Print help message.
  printHelp();
}

/***** Loop *****/

void loop() {
  if (Serial.available() > 0) {
    uint16_t size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = '\0';
    char* command = strtok(input, ";");
    if (command != NULL) {
      if (strcmp(command, "profile") == 0) {
        profileHandler();
      } else if (strcmp(command, "set") == 0) {
        setHandler();
      } else if (strcmp(command, "test") == 0) {
        testHandler();
      } else if (strcmp(command, "pulse") == 0) {
        pulseHandler();
      } else if (strcmp(command, "help") == 0) {
        helpHandler();
      } else {
        Serial.println(">>> Invaid command <<<");
        Serial.println("Comannd was: "+ String(command));
        Serial.println("");
      }
      while (command != NULL) {
        command = strtok(NULL, ";");
      }
    }
  }
}

/***** Command handlers *****/

// Command: profile
void profileHandler() {
  Serial.println(">>> Servo Profile <<<");
  Serial.println("0   degree pulse width: " + String(servo.pulseWidth0) + " ms");
  Serial.println("90  degree pulse width: " + String(servo.pulseWidth90) + " ms");
  Serial.println("180 degree pulse width: " + String(servo.pulseWidth180) + " ms");
  Serial.println("");
}

// Command: set;<reference degree>;<pulse width in ms>
void setHandler() {
  Serial.println(">>> Command: set <<<");
  char *degree = strtok(NULL, ";");
  char *pulse = strtok(NULL, ";");
  if (degree == NULL) {
    Serial.println("Missing reference degree value");
  } else if (pulse == NULL) {
    Serial.println("Missing pulse width value");
  } else {
    int val1 = String(degree).toInt();
    double val2 = String(pulse).toFloat();
    if (val1 == 0) {
      servo.pulseWidth0 = val2;
      Serial.println("Set " + String(val1) + " degree to: " + String(val2) + " ms");
    } else if (val1 == 90) {
      servo.pulseWidth90 = val2;
      Serial.println("Set " + String(val1) + " degree to: " + String(val2) + " ms");
    } else if (val1 == 180) {
      servo.pulseWidth180 = val2;
      Serial.println("Set " + String(val1) + " degree to: " + String(val2) + " ms");
    } else {
      Serial.println("Invalid reference degree: " + String(val1));
      Serial.println("Valid reference degrees are: 0, 90, 180");
    }
  }
  Serial.println("");
}

// Command: test;<turning angle in degrees>
void testHandler() {
  Serial.println(">>> Command: test <<<");
  char *degree = strtok(NULL, ";");
  if (degree != NULL) {
    double val1 = String(degree).toFloat();
    double val2 = servo.computePulseWidth(val1);
    pca9685.setServo(SERVO_INDEX, val2);
    Serial.println("Test servo with degree: " + String(val1) + ", pulse width: " + String(val2) + " ms");  
  } else {
    Serial.println("Missing degree value");
  }
  Serial.println("");
}

// Command: pulse;<pulse width in ms>
void pulseHandler() {
  Serial.println(">>> Command: pulse <<<");
  char *pulse = strtok(NULL, ";");
  if (pulse != NULL) {
    double val = String(pulse).toFloat();
    pca9685.setServo(SERVO_INDEX, val);
    Serial.println("Set servo pulse width to: " + String(val));  
  } else {
    Serial.println("Missing pulse width value");
  }
  Serial.println("");
}

// Command: help
void helpHandler() {
  printHelp();
}

/***** Helper functions *****/

void printWelcome() {
  Serial.println("");
  Serial.println(">>> PCA9685 Servo Controller Tool <<<");
  Serial.println("");
}

void printHelp() {
  Serial.println(">>> Available serial commands <<<");
  Serial.println("a) show current servo profile");
  Serial.println("   > profile;");
  Serial.println("b) set servo profile reference pulse width");
  Serial.println("   > set;<reference degree>;<pulse width in ms>");
  Serial.println("c) test servo profile with turning angle");
  Serial.println("   > test;<turning angle in degrees>");
  Serial.println("d) direct set servo pulse width");
  Serial.println("   > pulse;<pulse width in ms>");
  Serial.println("e) display help messages again");
  Serial.println("   > help;");
  Serial.println("");
}

