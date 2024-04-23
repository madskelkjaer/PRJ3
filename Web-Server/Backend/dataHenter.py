import sqlite3
import spidev
import time




con = sqlite3.connect("database.db")

cur = con.cursor()

try:
    cur.execute(
        "CREATE TABLE data(id INTEGER PRIMARY KEY, date TEXT, azimuth INTEGER, elevation INTEGER, batteristatus REAL)"
        )

    con.commit()
except:
    pass

def insertData(date, azimuth, elevation, batteristatus):
    cur.execute(
        "INSERT INTO data(date, azimuth, elevation, batteristatus) VALUES(?, ?, ?, ?)",
        (date, azimuth, elevation, batteristatus)
    )
    con.commit()

spi = spidev.SpiDev()
bus = 0
device = 0
spi.open(bus, device)

spi.max_speed_hz = 1000
spi.mode = 0

while True:
    to_send = [0x00]

    try:
        response = spi.xfer([0xff])
        print("Data sent: ", to_send)
        print("Data recieved: ", response)
    finally:
        spi.close()





insertData("2021-09-01 12:00:00", 180, 45, 100)