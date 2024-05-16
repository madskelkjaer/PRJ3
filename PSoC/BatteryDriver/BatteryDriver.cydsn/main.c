/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include"BatteryDriver.h"




int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char uartBuffer[256];
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_2_Start();
    ADC_SAR_2_StartConvert();

    for(;;)
    { 
        snprintf(uartBuffer, sizeof(uartBuffer), "Voltage divider: %i Percent\r\n", voltageDividerToPercent());
        //snprintf(UartBuffer, sizeof(UartBuffer), "Current hall: %i Volts\r\n", currentHall());
        UART_1_PutString(uartBuffer); 
    }
}



/* [] END OF FILE */
