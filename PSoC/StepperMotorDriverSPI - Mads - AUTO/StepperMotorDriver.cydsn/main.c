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
bool need_to_go_home = false;
bool left = false;
bool right = false;
bool up = false;
bool down = false;

void goHome()
{
    moveElevation(10000); // Go to home
    while (!limitUp()) {};
    CyDelay(100);
    moveElevation(-660);
    CyDelay(500);
    moveAzimuth(-10000);
    while (!limitRight()) {};
    CyDelay(100);
    moveAzimuth(3100);
    CyDelay(5000);
    resetAzimuth();
    resetElevation();
}

int countSensorsDetectingSun() {
    int count = 0;
    if (left) count++;
    if (right) count++;
    if (up) count++;
    if (down) count++;
    return count;
}

void automaticAction() {    
    UART_1_PutString("Automatisk \r\n");
    
    int current_sensors_detected = countSensorsDetectingSun();
    
    if (current_sensors_detected < 3) { // Hvis det ikke er den mest optimale position        
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
            current_time = 0; // Reset tiden <3
            break;
        case 2:
            // Move 100 steps right.
            moveAzimuth(-200);
            current_time = 0; // Reset tiden <3
            break;
        case 3:
            // Move 100 steps up.
            moveElevation(200);
            current_time = 0; // Reset tiden <3
            break;
        case 4:
            // Move 100 steps down.
            moveElevation(-200);
            current_time = 0; // Reset tiden <3
            break;
        case 7:
            goHome();
            current_time = 0; // Reset tiden <3
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
    
    if (recievedData == 10) {
        current_mode = MANUAL;
        UART_1_PutString("Manuel mode aktiveret!!\r\n"); 
    } else if (recievedData == 11) {
        current_mode = AUTOMATIC;
        UART_1_PutString("Automatisk mode aktiveret!!\r\n");  
    }
    
    switch (current_mode) {
        case AUTOMATIC:
            automaticAction();
            break;
        case MANUAL:
            manualAction(recievedData); // Håndter kommando.
            break;
    }
}

CY_ISR(TIMER_STEP) {
    current_time++; // Læg 1 til tiden.
    if (current_time > 30 && current_mode == MANUAL) current_mode = AUTOMATIC;
    if (current_time > 40 && current_mode == AUTOMATIC) {
        UART_1_PutString("20 min - Sol?: ");
        if (countSensorsDetectingSun() == 0) { // Hvis der ikke er sol mere,
            UART_1_PutString("NEJ \r\n");
            need_to_go_home = true;                       // Så sætter vi solcellen til hjem position.
        } else {
            UART_1_PutString("JA \r\n");
        }
        current_time = 0; // Resetter timeren.
    }
    
    char buff[64];
    sprintf(buff, "Current time: %i \r\n", current_time);
    UART_1_PutString(buff);
    Timer_1_ReadStatusRegister(); // Resetter timeren.
}

void setTimerEnable(bool enable) {
    if (enable) {
        Timer_1_Start();
        isr_timer_1_sek_StartEx(TIMER_STEP);
        return;
    }
    
    Timer_1_Stop();
}

void setSPIEnable(bool enable) {
    if (enable) {
        SPIS_1_ClearRxBuffer();
        SPIS_1_Start();
        isr_spis_1_rx_StartEx(SPI_RX_HANDLER);
        return;
    }
    
    SPIS_1_Stop();
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
    
    goHome();
    
    setTimerEnable(true);
    
    // Start SPI Slave component.
    setSPIEnable(true);
    
    int16_t batteryAmp = 0;
    int16_t voltage = 0;
    int16_t azimuth = 0;
    int16_t elevation = 0;
    for(;;) 
    {
        if (need_to_go_home) {
            setSPIEnable(false);
            setSPIEnable(false);
            goHome();
            need_to_go_home = false;
            setTimerEnable(true);
            setSPIEnable(true);
        }
        
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

        batteryAmp = scaledCurrentHall();
        int16_t batterAmpUnsigned = (int16_t)batteryAmp;
        int8_t batteryAmpHigh =(batterAmpUnsigned >> 8) & 0xFF;
        int8_t batteryAmpLow = batterAmpUnsigned & 0xFF;
        SPIS_1_WriteTxData(batteryAmpHigh);
        SPIS_1_WriteTxData(batteryAmpLow);
     
        
        left = sunLeft();
        right = sunRight();
        up = sunUp();
        down = sunDown();
        SPIS_1_WriteTxData(left);
        SPIS_1_WriteTxData(right);
        SPIS_1_WriteTxData(up);
        SPIS_1_WriteTxData(down);
        SPIS_1_WriteTxData(0xBB);
    }
}

/* [] END OF FILE */