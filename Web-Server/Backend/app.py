from flask import Flask, request, jsonify
from flask_cors import CORS
from flask_sock import Sock
import spidev
import json
import time
import sqlite3
import smtplib

### SQLITE ###
con = sqlite3.connect("database.db")
cur = con.cursor()

try:
    cur.execute(
        "CREATE TABLE data(id INTEGER PRIMARY KEY, date TEXT, azimuth INTEGER, elevation INTEGER, batteristatus INTEGER, sun_up INTEGER, sun_down INTEGER, sun_left INTEGER, sun_right INTEGER)"
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

        message = json.dumps({
            "date": date,
            "azimuth": azimuth,
            "elevation": elevation,
            "battery": batteristatus,
            "sun_up": sun_up,
            "sun_down": sun_down,
            "sun_left": sun_left,
            "sun_right": sun_right
        })

        for ws in ws_connections:
            try:
                ws.send(message)
            except:
                ws_connections.remove(ws)

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

spi.max_speed_hz = 10_000
spi.mode = 0

app = Flask(__name__)
running_status = False
manual_mode = False
CORS(app, resources={r"/api/*": {"origins": "*"}})
sock = Sock(app)
ws_connections = []
to_send = []

recieved_data: int = []

START_CODE = 0xAA
STOP_CODE = 0xBB
EXPECTED_DATA_LENGTH = 12

def bytesToInt16(high, low):
    value = (high << 8) | low
    if value >= 0x8000:
        value = value - 0x10000
    return value


def saveData(data):
    recieved_data.append(data)
    print("SAVEDATA: ", data, " LÆNGDE: ", len(recieved_data), "\nDATA I ARRAY: ", recieved_data)

    if len(recieved_data) < EXPECTED_DATA_LENGTH:
        return

    if recieved_data[0] == START_CODE and recieved_data[-1] == STOP_CODE:
        print("Data saved: ", recieved_data)
        AZIMUTH = bytesToInt16(recieved_data[1], recieved_data[2])
        ELEVATION = bytesToInt16(recieved_data[3], recieved_data[4])
        BATTERY = bytesToInt16(recieved_data[5], recieved_data[6])
        SUN_LEFT = recieved_data[7]
        SUN_RIGHT = recieved_data[8]
        SUN_UP = recieved_data[9]
        SUN_DOWN = recieved_data[10]

        print(f"{AZIMUTH=}, {ELEVATION=}, {BATTERY=}, {SUN_LEFT=}, {SUN_RIGHT=}, {SUN_UP=}, {SUN_DOWN=}")

        date = time.strftime("%Y-%m-%d %H:%M:%S")
        insertData(date, AZIMUTH, ELEVATION, BATTERY, SUN_UP, SUN_DOWN, SUN_LEFT, SUN_RIGHT)        
        recieved_data.clear()
    else:
        if recieved_data:
            recieved_data.pop(0)
        return

    if (len(recieved_data) < 7):
        return


def sendAndRecieveSpiData():
    if not len(to_send) > 0:
        to_send.append(0x00)

    data_to_send = to_send.pop(0)
    print("----")
    print("Sending data: ", data_to_send)
    print("Number of data in queue: ", len(to_send))
    try:
        response = spi.xfer([data_to_send])
        print("Data sent: ", data_to_send)
        print("Data received: ", response)
        saveData(response[0])
        print("----")
    except Exception as e:
        print("Error in sending data: ", e)

def runner():
    global running_status

    if running_status == True:
        return

    running_status = True

    while True:
        sendAndRecieveSpiData()
        time.sleep(0.2)

@app.route("/api/getdata/<int:limit>")
def getdata(limit: int):
    runner()
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
    elif direction == "azimuth":
        to_send.append(0x05)
    elif direction == "elevation":
        to_send.append(0x06)
    elif direction == "home":
        to_send.append(0x07)
    else:
        return "Invalid direction"
    
    return jsonify({"direction": direction})

@app.route("/api/manual")
def manual():
    global manual_mode
    manual_mode = not manual_mode

    to_send.append(0x10)

    message = json.dumps({
        "manual": manual_mode,
    })

    for ws in ws_connections:
        try:
            ws.send(message)
        except:
            ws_connections.remove(ws)

    manual_status = "activated" if manual_mode else "deactivated"
    return jsonify({"status": manual_status})

@app.route("/api/manual/status")
def manual_status():
    global manual_mode
    return jsonify({"status": manual_mode})

@app.route("/api/status")
def check_status():
    global running_status
    return jsonify({"status": running_status})

@app.route("/")
def hello_world():
    runner()
    to_send.append(0x00)
    return "<p>hejsa</p>"

# @app.route("/datarunner")
# def runner():
#     while True:
#         sendAndRecieveSpiData()
#         time.sleep(1)
#     return "Data runner is running continuously"

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

@sock.route("/api/ws")
def echo(ws):
    ws_connections.append(ws)
    while True:
        data = ws.receive()
        if data:
            ws.send(data)
        else:
            break

if __name__ == "__main__":
    app.run(port=5000)