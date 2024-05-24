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
#include <stdio.h>
#include "project.h"
#include "currentCalculation.h"

static char buff[256];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_2_Start();
    ADC_SAR_2_StartConvert();
    
    for(;;)
    {   
        snprintf(buff, sizeof(buff), "%f, %f \r\n", currentWAM(), currentSolar());
        UART_1_PutString(buff);
        CyDelay(30000);
    }
}

/* [] END OF FILE */
