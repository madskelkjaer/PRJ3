/* ========================================
 *
 * Andreas Strander Jakobsen
 * AU677469
 *
 * ========================================
*/
#include"BatteryDriver.h"


float currentHall()
{
    float sum = 0;
    
    for (int i = 0; i < 1000; i++)
    {
        //This iteration summarizes 1000 measurements, with the purpose of returning a mean value.
        int16_t result1 = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16());
        float convToAmps = (result1-2495)/0.3339;
        
        sum+= convToAmps;
    }
    //Returns the summarization divided with the amount of samples
    return sum/1000;
}

int16_t scaledCurrentHall() {
    float current = currentHall();
    // Scale the current to microamps (0.650 A -> 650000 uA)
    int scaledCurrent = (int)(current * 1000000); // scale to microamps
    if (scaledCurrent > 65535) {
        scaledCurrent = 65535; // Cap at the maximum value for uint16_t
    } else if (scaledCurrent < 0) {
        scaledCurrent = 0; // Ensure non-negative value
    }
    return (uint16_t)scaledCurrent;
}

int16_t voltageDividerToPercent()
{
   //Defines the upper and lower limit
   int16_t UpperLimit = 12000;
   int16_t LowerLimit = 8200;
    
   //Convertning the ADC value to milivolts
   int16_t result2 = ADC_SAR_2_CountsTo_mVolts(ADC_SAR_2_GetResult16());

   //Returns a scaled value, that shows the charge state of the battery
   int16_t scaled = (result2 * 3 - LowerLimit) * 100 / (UpperLimit - LowerLimit);

   return scaled > 100 ? 100 : (scaled < 0 ? 0 : scaled);
}

CY_ISR(ISR_UART_rx_handler)
{
    //ISR routine that handles the receiving data of the UART
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

/* [] END OF FILE */
