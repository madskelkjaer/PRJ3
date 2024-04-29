from flask import Flask
import flask-cors
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
finally:
    con.close()

def insertData(date, azimuth, elevation, batteristatus):
    try:
        con = sqlite3.connect("database.db")
        cur = con.cursor()
        cur.execute(
            "INSERT INTO data(date, azimuth, elevation, batteristatus) VALUES(?, ?, ?, ?)",
            (date, azimuth, elevation, batteristatus)
        )
        con.commit()
    except Exception as e:
        print("Error in inserting data: ", e)
    finally:
        con.close()

def getData(limit: int):
    try:
        con = sqlite3.connect("database.db")
        cur = con.cursor()
        cur.execute("SELECT * FROM data ORDER BY id DESC LIMIT ?", (limit,))
        data = cur.fetchall()
    except Exception as e:
        print("Error in inserting data: ", e)
    finally:
        con.close()
    
    return data

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

@app.route("/api/getdata/<int:limit>")
@cross_origin()
def getdata(limit: int):
    response = jsonify(getData(limit))
    response.response.headers.add("Access-Control-Allow-Origin", "*")
    return response

@app.route("/api/insertdata/<int:azimuth>/<int:elevation>/<float:batteristatus>")
def insertdata(azimuth: int, elevation: int, batteristatus: float):
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    insertData(date, azimuth, elevation, batteristatus)
    return "Data inserted"

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

@app.route("/saveForm")
def form():
    return "Form saved"
    
    

if __name__ == "__main__":
    app.run(threaded=True, port=5000)