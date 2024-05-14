#include "project.h"
#include "SunTracker.h"
#include "SensorDriver.h"
#include "StepperMotorDriver.h"
#include "SPI.h"

uint8_t receiveCommand(void);

int main(void) {
    CyGlobalIntEnable; // Enable global interrupts.

    SPI_Init();  // Initialize SPI for both slave data sending and receiving commands
    SPIS_1_Start(); // Start SPI Slave component for sending sensor data

    setMode(MODE_AUTO); // Start in automatic mode

    uint32_t lastTime = 0;
    uint32_t currentTime;
    const uint32_t delayInterval = 1200000; // Delay (20 min)

    // Define the array of data to send as uint16_t.
    uint8_t start = 0xAA;
    uint8_t stop = 0xBB;
    uint8_t azimuth = 10;
    uint8_t elevation = 20;
    uint8_t batteristatus = 30;
    uint8_t sun_left = 1;
    uint8_t sun_right = 0;
    uint8_t sun_up = 1;
    uint8_t sun_down = 0;

    uint16_t dataSequence[] = {
        start,
        azimuth,
        elevation,
        batteristatus,
        sun_left,
        sun_right,
        sun_up,
        sun_down,
        stop
    };

    while (true) {
        currentTime = CySysTickGetValue();

        if (getCurrentMode() == MODE_AUTO) {
            if ((currentTime - lastTime) >= delayInterval) {
                trackSun();  // Adjust the solar panel's position automatically
                lastTime = currentTime; // Update the last checked time
            }
        } else if (getCurrentMode() == MODE_MANUAL) {
            uint8_t command = receiveCommand();
            manualControl(command);
        }

        // Check if the SPI slave buffer is not empty.
        if(SPIS_1_GetRxBufferSize() != 0) {
            // Clear the buffer by reading from it.
            (void)SPIS_1_ReadRxData();  // Ignore the return value.

            // Send the array of data immediately after any SPI data is received.
            for (size_t i = 0; i < sizeof(dataSequence) / sizeof(dataSequence[0]); i++) {
                SPIS_1_WriteTxData((uint8_t)(dataSequence[i]));
            }
        }
    }

    return 0;
}

uint8_t receiveCommand(void) {
    return SPI_ReceiveData();
}
