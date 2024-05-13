/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include <stdbool.h>

// ISR functions
CY_ISR_PROTO(UART_HANDLER);
CY_ISR_PROTO(MOTOR_STEP);

// functions for azimuth motor
void moveAzimuth(int steps);
int azimuth();
void azimuthStep(int sequence[4]);

// functions for elevation motor
void moveElevation(int steps);
int elevation();
void elevationStep(int sequence[4]);

// function to get limit switches status
bool limitLeft();
bool limitRight();
bool limitUp();
bool limitDown();

/* [] END OF FILE */
