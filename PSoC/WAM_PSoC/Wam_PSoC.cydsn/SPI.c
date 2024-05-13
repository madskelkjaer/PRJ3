#include "SPI.h"

// Initialize the SPI component
void SPI_Init(void) {
    SPIS_1_Start(); // Assuming SPIS_1 is configured as the SPI slave
    CyGlobalIntEnable; // Enable global interrupts
}

// Send data over SPI
void SPI_SendData(uint8_t data) {
    while (!(SPIS_1_ReadTxStatus() & SPIS_1_STS_TX_FIFO_EMPTY)) {
        // Wait for TX buffer to be empty
    }
    SPIS_1_WriteTxData(data); // Write data to SPI
}

// Receive data from SPI
uint8_t SPI_ReceiveData(void) {
    while (!(SPIS_1_ReadRxStatus() & SPIS_1_STS_RX_FIFO_NOT_EMPTY)) {
        // Wait for data to be received
    }
    return SPIS_1_ReadRxData(); // Read received data from SPI
}
