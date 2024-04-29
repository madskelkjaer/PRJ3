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
to_send = []

def sendSpiData():
    if not len(to_send) > 0:
         to_send.append(0x00)
         
    data_to_send = to_send.pop(0)
    print("----")
    print("Sending data: ", data_to_send)
    try:
        response = spi.xfer([data_to_send])
        print("Data sent: ", data_to_send)
        print("Data received: ", response)
        print("----")
    except Exception as e:
        print("Error in sending data: ", e)

@app.route("/")
def hello_world():
    to_send.append(0xFF)
    return "<p>hejsa</p>"

@app.route("/datarunner")
def runner():
    while True:
        sendSpiData()
        time.sleep(1)
    return "Data runner is running continuously"

def sendMail():
    

if __name__ == "__main__":
    app.run(threaded=True, port=5000)