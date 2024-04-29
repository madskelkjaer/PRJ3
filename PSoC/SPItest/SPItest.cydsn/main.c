#include "project.h"

int main(void)
{
    CyGlobalIntEnable; // Enable global interrupts.

    // Start SPI Slave component.
    SPIS_1_Start();
    
    // Variable to hold received data.
    uint8 rxData;
    
    // Dummy data to send back.
    uint8 txData = 0xBB;
    uint8 expectedCommand = 0xFF; // Command expected from the master (Raspberry Pi)
    uint8 empty = 0x00;
    
    for(;;)
    {
        // Check if SPI slave buffer is not empty.
        if(SPIS_1_GetRxBufferSize() != 0)
        {
            // Read received data to clear the buffer.
            rxData = SPIS_1_ReadRxData();
            
            // Check if the received data matches the expected command.
            if(rxData == expectedCommand)
            {
                // Load the TX buffer with the dummy data only if the received command matches.
                SPIS_1_WriteTxData(txData);
            } else {
                SPIS_1_WriteTxData(empty);
            }
            
            // Optional: Toggle an LED or send a signal through a digital pin here as an indicator.
        }
    }
}