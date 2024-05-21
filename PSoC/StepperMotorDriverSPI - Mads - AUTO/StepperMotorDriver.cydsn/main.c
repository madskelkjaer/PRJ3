/* ========================================
 *
 *          Software holdet
 *
 * ========================================
*/

#include "project.h"
#include "StepperMotorDriver.h"
#include "SensorDriver.h"
#include "BatteryDriver.h"

#include "Mode.h"
#include <stdio.h>

volatile enum mode current_mode = AUTOMATIC;
uint16_t current_time = 0;

void goHome()
{
    moveElevation(10000); // Go to home
    CyDelay(5000);
    moveElevation(-660);
    CyDelay(2000);
    moveAzimuth(-10000);
    CyDelay(5000);
    moveAzimuth(3100);
    CyDelay(5000);
    resetAzimuth();
    resetElevation();
}


int countSensorsDetectingSun() {
    int count = 0;
    if (sunLeft()) count++;
    if (sunRight()) count++;
    if (sunUp()) count++;
    if (sunDown()) count++;
    return count;
}

void automaticAction() {
    int current_sensors_detected = countSensorsDetectingSun();
    
    if (current_time > 1200) {
        if (current_sensors_detected == 0) {
            goHome();
        }
        
        current_time = 0;
    }
    
    if (current_sensors_detected < 3) {
        // Read sensor statuses
        bool left = sunLeft();
        bool right = sunRight();
        bool up = sunUp();
        bool down = sunDown();

        // Determine horizontal movement
        if (left && !right) {
            moveAzimuth(-50); // Move left
        } else if (right && !left) {
            moveAzimuth(50); // Move right
        }

        // Determine vertical movement
        if (up && !down) {
            moveElevation(50); // Move up
        } else if (down && !up) {
            moveElevation(-50); // Move down
        }

        CyDelay(100); // Small delay to allow motors to move
    }
}

void manualAction(uint8_t command) {
    switch (command)
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
        case 7:
            goHome();
            break;
        default:
            // Ignore other commands.
            break;
    }
}

CY_ISR(SPI_RX_HANDLER)
{ 
    if (SPIS_1_GetRxBufferSize() == 0) {
        return;
    }
    
    // UART_1_PutString("Modtog SPI interrupt");
    uint8_t recievedData = SPIS_1_ReadRxData();
    
    char buff[64];
    snprintf(buff, sizeof(buff), "Data: %i  \r\n", recievedData);
    UART_1_PutString(buff);
    
    switch (recievedData)
    {
        case 10:
            current_mode = MANUAL;
        case 11:
            current_mode = AUTOMATIC;
        default:
            break;
    }
    
    switch (current_mode) {
        case AUTOMATIC:
            automaticAction();
            break;
        case MANUAL:
            if (current_time > 1200) {
                current_mode = AUTOMATIC;
            } else {
                current_time = 0;
                manualAction(recievedData);
            }
            break;
              
    }
    
    MOTOR_STEP();
}

CY_ISR(TIMER_STEP) {
    current_time++;
}

int main(void)
{
    CyGlobalIntEnable;
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_2_Start();
    ADC_SAR_2_StartConvert();
    isr_motor_StartEx(MOTOR_STEP);
    UART_1_PutString("WAM!\r\n");
    Timer_1_Start();
    isr_timer_1_sek_StartEx(TIMER_STEP);
    
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
        int16_t azimuthUnsigned = (int16_t)azimuth;
        int8_t azimuthHigh = (azimuthUnsigned >> 8) & 0xFF;
        int8_t azimuthLow = azimuthUnsigned & 0xFF;
        SPIS_1_WriteTxData(azimuthHigh);
        SPIS_1_WriteTxData(azimuthLow);
        
        elevation = getElevation();
        int16_t elevationUnsigned = (int16_t)elevation;
        int8_t elevationHigh = (elevationUnsigned >> 8) & 0xFF;
        int8_t elevationLow = elevationUnsigned & 0xFF;
        SPIS_1_WriteTxData(elevationHigh);
        SPIS_1_WriteTxData(elevationLow);
        
        voltage = voltageDividerToPercent();
        int16_t voltageUnsigned = (int16_t)voltage;
        int8_t voltageHigh = (voltageUnsigned >> 8) & 0xFF;
        int8_t voltageLow = voltageUnsigned & 0xFF;

        SPIS_1_WriteTxData(voltageHigh);
        SPIS_1_WriteTxData(voltageLow);
        
        int8_t left = sunLeft() ? 1 : 0;
        int8_t right = sunRight() ? 1 : 0;
        int8_t up = sunUp() ? 1 : 0;
        int8_t down = sunDown() ? 1 : 0;
        SPIS_1_WriteTxData(left);
        SPIS_1_WriteTxData(right);
        SPIS_1_WriteTxData(up);
        SPIS_1_WriteTxData(down);
        SPIS_1_WriteTxData(0xBB);
    }
}

/* [] END OF FILE */