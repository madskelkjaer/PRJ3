/* ========================================
 *
 * Andreas Strander Jakobsen
 * AU677469
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

// ISR routine for UART
CY_ISR_PROTO(ISR_UART_rx_handler);

// Standard library Function for handling receiving data
void handleByteReceived(uint8_t byteReceived);

// Function to get the voltage signal from the ADC and returns it as an int16_t
float currentHall(); 

// Function to get the scaled battery current 
uint16_t scaledCurrentHall(); 

// Function that converts the voltage dividers signal, and returns it as a percentage
int16_t voltageDividerToPercent(); 

/* [] END OF FILE */
