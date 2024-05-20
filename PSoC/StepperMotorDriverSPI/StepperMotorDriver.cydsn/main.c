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
    UART_1_PutString("Ready to test new ideas that don't work!\r\n");       // Show message on UART on startup
    
    // Start SPI Slave component.
    SPIS_1_Start();
    
    uint8_t receivedData = 0;

    for(;;) 
    {
        // SPI Communication Handling
        if (SPIS_1_GetRxBufferSize() != 0)
        {
            // Read the received data.
            receivedData = SPIS_1_ReadRxData();

            switch (receivedData)
            {
                case 1:
                    // Move 100 steps left.
                    moveAzimuth(100);
                    break;
                case 2:
                    // Move 100 steps right.
                    moveAzimuth(-100);
                    break;
                case 3:
                    // Move 100 steps up.
                    moveElevation(100);
                    break;
                case 4:
                    // Move 100 steps down.
                    moveElevation(-100);
                    break;
                default:
                    // Ignore other commands.
                    break;
            }
        }

        MOTOR_STEP();
        
        // UART Communication Handling
        char buff[64];
        snprintf(buff, sizeof(buff), "Up: %i, Down: %i, Right: %i, Left: %i  \r\n", limitUp(), limitDown(), limitRight(), limitLeft());
        UART_1_PutString(buff);
    }
}

/* [] END OF FILE */