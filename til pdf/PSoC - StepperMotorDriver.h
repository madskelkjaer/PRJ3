/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include <stdbool.h>

// ISR functions
CY_ISR_PROTO(MOTOR_STEP);

int16_t getAzimuth();
int16_t getElevation();
void resetAzimuth();
void resetElevation();

// functions for azimuth motor
void moveAzimuth(int steps);
void azimuth();
void azimuthStep(int sequence[4]);

// functions for elevation motor
void moveElevation(int steps);
void elevation();
void elevationStep(int sequence[4]);

// function to get limit switches status
bool limitLeft();
bool limitRight();
bool limitUp();
bool limitDown();

/* [] END OF FILE */
