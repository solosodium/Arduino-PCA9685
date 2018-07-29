#ifndef SERVOPROFILE_H
#define SERVOPROFILE_H

#include <algorithm>

/**
 * A utility class maps 0 to 180 degrees to predefined servo pulse width.
 * It takes 3 reference pulse width at 0, 90 and 180 degrees, and
 * interpolates input angle in degree to corresponding pulse width using
 * second order curve fitting.
 */
class ServoProfile {

private:

    // Default pulse width values.
    static const double PULSE_WIDTH_0_DEFAULT;
    static const double PULSE_WIDTH_90_DEFAULT;
    static const double PULSE_WIDTH_180_DEFAULT;

public:

    // Internal pulse width in miliseconds (usually 1~2).
    double pulseWidth0;
    double pulseWidth90;
    double pulseWidth180;

    // Default constructor.
    ServoProfile();

    // Constructor with pulse widths.
    ServoProfile(double pw0, double pw90, double pw180);

    // Compute servo pulse width with input angle in degrees (0~180).
    double computePulseWidth(double angle);
};

#endif

