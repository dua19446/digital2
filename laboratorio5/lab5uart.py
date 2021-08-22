from Adafruit_IO import Client, RequestError, Feed
from time import sleep
import serial
import time
import sys

Ennable = 1

CONT = ["","",""]
centenas = 0
decenas = 0
unidades = 0
enviar = 0 
# Se crea el cliente en Adafruit_IO
ADAFRUIT_IO_KEY = "aio_nmSa16ffaXfWBS4sdME2dOamGIYk"
ADAFRUIT_IO_USERNAME = "AlexD10"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Se establecen los feeds que se utilizaran
#contador_recibido = aio.feeds('contador-recibido')
sr1_feed = aio.feeds('sensor-1')
sr2_feed = aio.feeds('sensor-2')

comu=serial.Serial() # se crea puerto Serial
comu.baudrate=9600 # se establece baudrate
comu.timeout=3 # Se estlece tiempo para recibir datos
# Se define el puerto con el del FTDI
comu.port='COM2'

comu.open()
print('comunicacion exitosa')
    
comu.write(b'a')
print('se envio mensaje')

    
centenas = comu.readline(1).decode('ascii','ignore')
decenas = comu.readline(1).decode('ascii','ignore')
unidades = comu.readline(1).decode('ascii','ignore')
contador_b = int(centenas+decenas+unidades)
print('se recibieron datos')
aio.send_data(sr1_feed.key, contador_b)
enviando = aio.receive(sr2_feed.key)
enviar = enviando.value
centena = enviar[0:1].encode('ascii','ignore')
decena = enviar[1:2].encode('ascii','ignore')
unidad = enviar[2:3].encode('ascii','ignore')
comu.write(centena)
time.sleep(0.01)
comu.write(decena)
time.sleep(0.01)
comu.write(unidad)


