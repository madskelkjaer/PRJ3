#include "project.h"
#include "SunTracker.h"
#include "SensorDriver.h"
#include "StepperMotorDriver.h"
#include "SPI.h"

uint8_t receiveCommand(void);

int main(void) {
    CyGlobalIntEnable; // Enable global interrupts.

    SPI_Init();  // Initialize SPI

    setMode(MODE_AUTO); // Start in automatic mode

    uint32_t lastTime = 0;
    uint32_t currentTime;
    const uint32_t delayInterval = 1200000; // Delay (20 min)

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
    }

    return 0;
}

uint8_t receiveCommand(void) {
    return SPI_ReceiveData();
}
