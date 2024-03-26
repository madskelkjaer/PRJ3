import spidev
import time


spi = spidev.SpiDev()
spi.open(0, 0)

file_path = 'spi_data.txt'

def read_spi_and_write_to_file():
    while True:
        # læs spi hehe
        spi_data = spi.readbytes(1)
        # spi til int så den kan bruges 
        spi_value = int.from_bytes(spi_data, byteorder='big')
        
        # skriv til spi fil kode dims
        with open(file_path, 'a') as file:
            file.write(str(spi_value) + '\n')
        
        time.sleep(0.1)

if __name__ == "__main__":
    read_spi_and_write_to_file()
