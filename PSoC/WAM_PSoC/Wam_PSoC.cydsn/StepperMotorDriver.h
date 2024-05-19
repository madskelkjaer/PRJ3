/* ========================================
 *
 *          Thomas Degn Larsen og Per Clausen
 *
 * ========================================
*/

#include "project.h"
#include <stdbool.h>

// ISR functions
CY_ISR_PROTO(UART_HANDLER);
CY_ISR_PROTO(MOTOR_STEP);

// Functions for azimuth motor
void moveAzimuth(int steps);
void azimuth();
void azimuthStep(int sequence[4]);

// Functions for elevation motor
void moveElevation(int steps);
void elevation();
void elevationStep(int sequence[4]);

// Function to get limit switches status
bool limitLeft();
bool limitRight();
bool limitUp();
bool limitDown();

// Functions to set and get the current position
void setStartPosition(void);
int32_t getAzimuthPosition(void);
int32_t getElevationPosition(void);

/* [] END OF FILE */
