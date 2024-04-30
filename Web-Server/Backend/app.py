from flask import Flask, request
from flask_cors import CORS
import spidev
import time
import sqlite3
import smtplib

### SQLITE ###
con = sqlite3.connect("database.db")
cur = con.cursor()

try:
    cur.execute(
        "CREATE TABLE data(id INTEGER PRIMARY KEY, date TEXT, azimuth INTEGER, elevation INTEGER, batteristatus REAL, sun_up INTEGER, sun_down INTEGER, sun_left INTEGER, sun_right INTEGER)"
        )

    con.commit()
except:
    pass
finally:
    con.close()

def sendEmail(name, email, message):
    mail = smtplib.SMTP('mail.madse.nu', 465)
    mail.ehlo()
    mail.starttls()
    mail.login('wam@madse.nu', 'wamersejt')
    header = 'To:' + email + '\n' + 'From:' \
            + 'wam@madse.nu' + '\n' + 'Subject: Modtaget ny besked fra '+name+' \n'
    content = header + message
    mail.sendmail('wam@madse.nu', email, content) # (1) = Sender, (2) = Receiver
    mail.close



def insertData(date, azimuth, elevation, batteristatus, sun_up, sun_down, sun_left, sun_right):
    try:
        con = sqlite3.connect("database.db")
        cur = con.cursor()
        cur.execute(
            "INSERT INTO data(date, azimuth, elevation, batteristatus, sun_up, sun_down, sun_left, sun_right) VALUES(?, ?, ?, ?, ?, ?, ?, ?)",
            (date, azimuth, elevation, batteristatus, sun_up, sun_down, sun_left, sun_right)
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
CORS(app, resources={r"/api/*": {"origins": "*"}})
to_send = []

recieved_data: int = []

def saveData(data):
    recieved_data.append(data)
    print("SAVEDATA: ", data, " LÆNGDE: ", len(recieved_data))

    if (len(recieved_data) < 7):
        return
    
    print("Data saved: ", recieved_data)
    AZIMUTH = recieved_data[1]
    ELEVATION = recieved_data[2]
    BATTERY = recieved_data[3]
    SUN_LEFT = recieved_data[4]
    SUN_RIGHT = recieved_data[5]
    SUN_UP = recieved_data[6]
    SUN_DOWN = recieved_data[7]

    date = time.strftime("%Y-%m-%d %H:%M:%S")
    insertData(date, AZIMUTH, ELEVATION, BATTERY, SUN_UP, SUN_DOWN, SUN_LEFT, SUN_RIGHT)
    recieved_data.clear()


def sendAndRecieveSpiData():
    if not len(to_send) > 0:
         to_send.append(0x00)
         
    data_to_send = to_send.pop(0)
    print("----")
    print("Sending data: ", data_to_send)
    try:
        response = spi.xfer([data_to_send])
        saveData(response[0])
        print("Data sent: ", data_to_send)
        print("Data received: ", response)
        print("----")
    except Exception as e:
        print("Error in sending data: ", e)

@app.route("/api/getdata/<int:limit>")
def getdata(limit: int):
    return getData(limit)

@app.route("/api/move/<string:direction>")
def move(direction: str):
    if direction == "left":
        to_send.append(0x01)
    elif direction == "right":
        to_send.append(0x02)
    elif direction == "up":
        to_send.append(0x03)
    elif direction == "down":
        to_send.append(0x04)
    elif direction == "home":
        to_send.append(0x05)
    else:
        return "Invalid direction"
    
    return "Moving " + direction

@app.route("/")
def hello_world():
    to_send.append(0x00)
    return "<p>hejsa</p>"

@app.route("/datarunner")
def runner():
    while True:
        sendAndRecieveSpiData()
        # time.sleep(1)
    return "Data runner is running continuously"

@app.route("/api/inserttestdata")
def inserttestdata():
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    insertData(date, 240, 69, 100.0, 1, 0, 1, 0)
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    insertData(date, 69, 100, 98.0, 0, 1, 1, 0)
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    insertData(date, 64, 432, 95.0, 1, 1, 0, 0)
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    return "Data inserted"

@app.route("/api/saveform", methods=["POST"])
def form():
    # Hent data fra anmodningen
    print("DATA")
    data = request.form
    name = data['name']
    email = data['email']
    message = data['message']
    print(name, email, message)
    sendEmail(name, email, message)
    return "Data modtaget"

if __name__ == "__main__":
    app.run(threaded=True, port=5000)