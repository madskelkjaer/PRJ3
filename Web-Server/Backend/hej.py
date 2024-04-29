import spidev
import time

spi = spidev.SpiDev()
bus = 0
device = 0
spi.open(bus, device)

spi.max_speed_hz = 1000
spi.mode = 0

to_send = [0xff]

try:
	response = spi.xfer([0xff])
	print("Data sent: ", to_send)
	print("Data recieved: ", response)
finally:
	spi.close()


