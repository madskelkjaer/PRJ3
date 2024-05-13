#ifndef SUN_TRACKER_H
#define SUN_TRACKER_H

#include <stdint.h> // Include standard integer type definitions

// Define operation modes
#define MODE_AUTO 1
#define MODE_MANUAL 0

// Function declarations
void trackSun(void);              // Function to track the sun automatically
void setMode(uint8_t mode);       // Function to set the current mode
void manualControl(uint8_t command); // Function for manual control
int getCurrentMode(void);         // Function to get the current mode

#endif // SUN_TRACKER_H
