#include "SunTracker.h"
#include "SensorDriver.h"
#include "StepperMotorDriver.h"
#include "BatteryDriver.h"
#include "Mode.h"

extern enum mode current_mode;

void manualControl(uint8_t command) {
    if (currentMode == MODE_MANUAL) {
        // Switch-case to move motors
        switch(command) {
            case 1: // Command for moving left
                moveAzimuth(-250); // Move left by 250 steps
                break;
            case 2: // Command for moving right
                moveAzimuth(250); // Move right by 250 steps
                break;
            case 3: // Command for moving up
                moveElevation(250); // Move up by 250 steps
                break;
            case 4: // Command for moving down
                moveElevation(-250); // Move down by 250 steps
                break;
            default:
                // Error Handling?
                break;
        }
    }
}

int getCurrentMode(void) {
    return currentMode;
}

int countSensorsDetectingSun() {
    int count = 0;
    if (sunLeft()) count++;
    if (sunRight()) count++;
    if (sunUp()) count++;
    if (sunDown()) count++;
    return count;
}

void trackSun(void) {
    // Function to track the sun automatically

    while (countSensorsDetectingSun() < 3) {
        // Read sensor statuses
        bool left = sunLeft();
        bool right = sunRight();
        bool up = sunUp();
        bool down = sunDown();

        // Determine horizontal movement
        if (left && !right) {
            moveAzimuth(-50); // Move left
        } else if (right && !left) {
            moveAzimuth(50); // Move right
        }

        // Determine vertical movement
        if (up && !down) {
            moveElevation(50); // Move up
        } else if (down && !up) {
            moveElevation(-50); // Move down
        }

        CyDelay(100); // Small delay to allow motors to move
    }
}

void sendData(void) {
    uint8_t start = 0xAA;                // Start
    uint16_t azimuth = (uint16_t)getAzimuthPosition();  // Actual azimuth position, full range
    uint16_t elevation = (uint16_t)getElevationPosition(); // Actual elevation position, full range
    uint16_t batteryAmp = scaledCurrentHall();  // Scaled battery current in microamps
    uint8_t batteryStatus = (uint8_t)voltageDividerToPercent();  // Define battery status, in percentage
    uint8_t sun_left = sunLeft();        // Define sun sensor on the left
    uint8_t sun_right = sunRight();      // Define sun sensor on the right
    uint8_t sun_up = sunUp();            // Define sun sensor up
    uint8_t sun_down = sunDown();        // Define sun sensor down
    uint8_t stop = 0xBB;                 // Stop
    
    // Data to send (note the 16-bit positions and current are split into two bytes)
    uint8_t dataSequence[] = {
        start,
        (uint8_t)(azimuth >> 8), // High byte of azimuth
        (uint8_t)(azimuth & 0xFF), // Low byte of azimuth
        (uint8_t)(elevation >> 8), // High byte of elevation
        (uint8_t)(elevation & 0xFF), // Low byte of elevation
        (uint8_t)(batteryAmp >> 8), // High byte of battery current
        (uint8_t)(batteryAmp & 0xFF), // Low byte of battery current
        batteryStatus,
        sun_left,
        sun_right,
        sun_up,
        sun_down,
        stop
    };
    
    // Transmit data over SPI (assuming SPIS_1 is the SPI component used)
    for (size_t i = 0; i < sizeof(dataSequence); i++) {
        SPIS_1_WriteTxData(dataSequence[i]);
    }
}
