import serial

#Se crea un puerto serial para la comunicaion
puerto=serial.Serial()
puerto.baudrate=9600
puerto.timeout=3
puerto.port='COM3'

from Adafruit_IO import Client, RequestError, Feed
ADAFRUIT_IO_KEY = "aio_sMMD47AClfsoBtLJNiZv5febwaH8"
ADAFRUIT_IO_USERNAME = "AlexD10"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

sr1_feed = aio.feeds('sensor-1')
aio.send_data(sr1_feed.key, 0)
sr1_data = aio.receive(sr1_feed.key)
print(f'analog signal: {sr1_data.value}')

puerto.write(sr1_data)
respuesta = puerto.readline()
aio.send_data(sr1_feed.key, respuesta)

sr2_feed = aio.feeds('sensor-2')
aio.send_data(sr2_feed.key, 0)
sr2_data = aio.receive(sr2_feed.key)
print(f'digital signal: {sr2_data.value}')
