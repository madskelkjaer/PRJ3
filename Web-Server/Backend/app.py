from flask import Flask
import spidev
import time
import sqlite3


### SQLITE ###
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


### SPI DEV ###
spi = spidev.SpiDev()
bus = 0
device = 0
spi.open(bus, device)

spi.max_speed_hz = 1000
spi.mode = 0





app = Flask(__name__)

def sendSpiData(data):
	print("Data: ", data)
	try:
		response = spi.xfer(data)
		print("Data sent: ", data)
		print("Data recieved: ", response)
	finally:
		spi.close()


@app.route("/")
def hello_world():
	to_send.append(0xff)
	return "<p>hejsa</p>"

@app.route("/datarunner")
def runner():
	global to_send
	to_send = []

	while True:
		if (len(to_send) == 0):
			to_send.append(0x00)
		sendSpiData(to_send)

		time.sleep(1)

		yield "Running"

	return "Data runner is running continuously"
	

if __name__ == "__main__":
	app.run(threaded=True, port=5000)
