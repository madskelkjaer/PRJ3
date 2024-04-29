/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include "StepperMotorDriver.h"
#include <stdio.h>

int main(void)
{
    CyGlobalIntEnable;                                                      // Enable global interrupts.
    UART_1_Start();                                                         // Enable UART
    isr_uart_rx_StartEx(UART_HANDLER);                                      // Enable UART ISR
    isr_motor_StartEx(MOTOR_STEP);                                          // Enable ISR for motor speed
    UART_1_PutString("Ready to test new ideas that doesn't work!\r\n");     // Show message on UART on startup
   
    for(;;) 
    {
        /*char buff[64];
        snprintf(buff, sizeof(buff), "Up: %i, Down: %i, Right: %i, Left: %i  \r\n", limitUp(), limitDown(), limitRight(), limitLeft());
        UART_1_PutString(buff);*/
    }
}

/* [] END OF FILE */