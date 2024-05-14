import spidev
import time

### SPI DEV ###
spi = spidev.SpiDev()
bus = 0
device = 0
spi.open(bus, device)

spi.max_speed_hz = 1000
spi.mode = 0

while True:
    inputtet = input("Enter data to send (q to quit): ")

    if inputtet == "":
        inputtet = 0
    
    if inputtet == "q":
        spi.close()
        break
    
    print("----")
    print("Sending data: ", inputtet)
    try:
        response = spi.xfer([int(inputtet)])
        print("Data sent: ", inputtet)
        print("Data received: ", response)
        print("----")
    except Exception as e:
        print("Error in sending data: ", e)



