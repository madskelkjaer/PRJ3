/* ========================================
 *
 *          Thomas Degn Larsen
 *
 * ========================================
*/

#include "project.h"
#include "StepperMotorDriver.h"
#include "SensorDriver.h"
#include"BatteryDriver.h"
#include <stdio.h>

CY_ISR(SPI_RX_HANDLER)
{
    if (SPIS_1_GetRxBufferSize() == 0) {
        return;
    }
    
    // UART_1_PutString("Modtog SPI interrupt");
    uint8_t recievedData = SPIS_1_ReadRxData();
    
    // char buff[64];
    // snprintf(buff, sizeof(buff), "Data: %i  \r\n", recievedData);
    // UART_1_PutString(buff);
    
    switch (recievedData)
    {
        case 1:
            // Move 100 steps left.
            moveAzimuth(200);
            break;
        case 2:
            // Move 100 steps right.
            moveAzimuth(-200);
            break;
        case 3:
            // Move 100 steps up.
            moveElevation(200);
            break;
        case 4:
            // Move 100 steps down.
            moveElevation(-200);
            break;
        default:
            // Ignore other commands.
            break;
    }
    
    MOTOR_STEP();    
}

void goHome()
{
    moveElevation(10000); // Go to home
    CyDelay(5000);
    moveElevation(-640);
    CyDelay(2000);
    moveAzimuth(-10000);
    CyDelay(5000);
    moveAzimuth(3100);
    CyDelay(5000);
    resetAzimuth();
    resetElevation();
}

int main(void)
{
    CyGlobalIntEnable;                                                      // Enable global interrupts.
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_2_Start();
    ADC_SAR_2_StartConvert();
    isr_motor_StartEx(MOTOR_STEP);                                          // Enable ISR for motor speed
    UART_1_PutString("Ready to test new ideas that don't work!\r\n");       // Show message on UART on startup
    
    // Start SPI Slave component.
    SPIS_1_Start();
    isr_spis_1_rx_StartEx(SPI_RX_HANDLER);
    
    goHome();
    

    int16_t voltage = 0;
    int16_t azimuth = 0;
    int16_t elevation = 0;
    for(;;) 
    {
        SPIS_1_WriteTxData(0xAA);
        
        azimuth = getAzimuth();
        uint16_t azimuthUnsigned = (uint16_t)azimuth;
        uint8_t azimuthHigh = (azimuthUnsigned >> 8) & 0xFF;
        uint8_t azimuthLow = azimuthUnsigned & 0xFF;
        SPIS_1_WriteTxData(azimuthHigh);
        SPIS_1_WriteTxData(azimuthLow);
        
        elevation = getElevation();
        uint16_t elevationUnsigned = (uint16_t)elevation;
        uint8_t elevationHigh = (elevationUnsigned >> 8) & 0xFF;
        uint8_t elevationLow = elevationUnsigned & 0xFF;
        SPIS_1_WriteTxData(elevationHigh);
        SPIS_1_WriteTxData(elevationLow);
        
        voltage = voltageDividerToPercent();
        uint16_t voltageUnsigned = (uint16_t)voltage;
        uint8_t voltageHigh = (voltageUnsigned >> 8) & 0xFF;
        uint8_t voltageLow = voltageUnsigned & 0xFF;

        SPIS_1_WriteTxData(voltageHigh);
        SPIS_1_WriteTxData(voltageLow);
        
        uint8_t left = sunLeft() ? 1 : 0;
        uint8_t right = sunRight() ? 1 : 0;
        uint8_t up = sunUp() ? 1 : 0;
        uint8_t down = sunDown() ? 1 : 0;
        SPIS_1_WriteTxData(left);
        SPIS_1_WriteTxData(right);
        SPIS_1_WriteTxData(up);
        SPIS_1_WriteTxData(down);
        SPIS_1_WriteTxData(0xBB);
    }
}

/* [] END OF FILE */