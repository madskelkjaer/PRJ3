#include "SunTracker.h"
#include "SensorDriver.h"
#include "StepperMotorDriver.h"

static int currentMode = MODE_AUTO; // Default is automatic mode

void trackSun(void) {
    if (currentMode == MODE_AUTO) {
        // Sun-tracking logic
        bool sun_left = sunLeft();
        bool sun_right = sunRight();
        bool sun_up = sunUp();
        bool sun_down = sunDown();

        // Move azimuth
        if (sun_left && !sun_right && !limitLeft()) {
            moveAzimuth(-10); // Move panel left by 10 steps
        } else if (sun_right && !sun_left && !limitRight()) {
            moveAzimuth(10); // Move panel right by 10 steps
        }

        // Move elevation
        if (sun_up && !sun_down && !limitUp()) {
            moveElevation(10); // Tilt panel up by 10 steps
        } else if (sun_down && !sun_up && !limitDown()) {
            moveElevation(-10); // Tilt panel down by 10 steps
        }
    }
}

void setMode(uint8_t command) {
    if (command == 0x10) {
        // Toggle mode between manual and automatic
        if (currentMode == MODE_AUTO) {
            currentMode = MODE_MANUAL;
        } else {
            currentMode = MODE_AUTO;
        }
    }
}

void manualControl(uint8_t command) {
    if (currentMode == MODE_MANUAL) {
        // Switch-cases to move motors
        switch(command) {
            case 0x01: // Command for moving left
                if (!limitLeft()) {
                    moveAzimuth(-10); // Move left by 10 steps
                }
                break;
            case 0x02: // Command for moving right
                if (!limitRight()) {
                    moveAzimuth(10); // Move right by 10 steps
                }
                break;
            case 0x03: // Command for moving up
                if (!limitUp()) {
                    moveElevation(10); // Move up by 10 steps
                }
                break;
            case 0x04: // Command for moving down
                if (!limitDown()) {
                    moveElevation(-10); // Move down by 10 steps
                }
                break;
            default:
                //Error Handling?
                break;
        }
    }
}

int getCurrentMode(void) {
    return currentMode;
}
