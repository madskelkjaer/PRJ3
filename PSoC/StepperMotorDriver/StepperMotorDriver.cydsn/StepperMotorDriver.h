/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"

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

/* [] END OF FILE */
