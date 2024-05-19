#include "project.h"
#include "SunTracker.h"
#include "StepperMotorDriver.h"
#include <stdio.h>

#define AUTO_MODE_INTERVAL 20 * 60 * 1000 // 20 minutes in milliseconds, adjustable

CY_ISR(SPI_ISR) {
    if (SPIS_1_GetRxBufferSize() > 0) {
        uint8_t command = SPIS_1_ReadRxData();
        if (command == 16) {
            setMode(command);
        } else {
            manualControl(command);
        }
    }
}

int main(void) {
    CyGlobalIntEnable;  // Enable global interrupts.
    UART_1_Start();  // Enable UART
    isr_uart_rx_StartEx(UART_HANDLER);  // Enable UART ISR
    isr_motor_StartEx(MOTOR_STEP);  // Enable ISR for motor speed
    isr_spi_StartEx(SPI_ISR);  // Enable ISR for SPI (Ensure isr_spi is the correct name in your project)
    
    SPIS_1_Start();  // Start SPI slave component
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    ADC_SAR_2_Start();
    ADC_SAR_2_StartConvert();
    
    setStartPosition();  // Set the initial position of the motors
    
    UART_1_PutString("Ready to test new ideas that don't work!\r\n");  // Show message on UART on startup

    uint32_t lastAutoModeUpdateTime = 0;
    
    for(;;) {
        uint32_t currentTime = CySysTickGetValue(); // Get current time
        
        if (getCurrentMode() == MODE_AUTO) {
            if (currentTime - lastAutoModeUpdateTime >= AUTO_MODE_INTERVAL) {
                trackSun(); // Adjust to the best position for the sun
                lastAutoModeUpdateTime = currentTime;
            }
        }

        sendData();  // Send data to the Raspberry Pi
        
        char buff[64];
        snprintf(buff, sizeof(buff), "Up: %i, Down: %i, Right: %i, Left: %i  \r\n", limitUp(), limitDown(), limitRight(), limitLeft());
        UART_1_PutString(buff);
        
        CyDelay(1000);  // Adjust delay as needed
    }
}
