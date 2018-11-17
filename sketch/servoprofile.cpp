#include "servoprofile.h"

const double ServoProfile::PULSE_WIDTH_0_DEFAULT = 1.0;
const double ServoProfile::PULSE_WIDTH_90_DEFAULT = 1.5;
const double ServoProfile::PULSE_WIDTH_180_DEFAULT = 2.0;

ServoProfile::ServoProfile() {
    pulseWidth0 = PULSE_WIDTH_0_DEFAULT;
    pulseWidth90 = PULSE_WIDTH_90_DEFAULT;
    pulseWidth180 = PULSE_WIDTH_180_DEFAULT;
}

ServoProfile::ServoProfile(double pw0, double pw90, double pw180) {
    pulseWidth0 = pw0;
    pulseWidth90 = pw90;
    pulseWidth180 = pw180;
}

double ServoProfile::computePulseWidth(double angle) {
    // Angle should be within 0~180 degrees, and map it to 0~1.
    angle = angle < 0.0 ? 0.0 : angle;
    angle = angle > 180.0 ? 180.0 : angle;
    angle = angle / 180.0;
    // Use second order curve fitting to find corresponding pulse width.
    double a = 2.0 * pulseWidth0 - 4.0 * pulseWidth90 + 2.0 * pulseWidth180;
    double b = -3.0 * pulseWidth0 + 4.0 * pulseWidth90 - pulseWidth180;
    double c = pulseWidth0;
    return a * angle * angle + b * angle + c;
}

