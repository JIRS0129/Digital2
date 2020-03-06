from Adafruit_IO import RequestError, Client, Feed
from random import *
import time

ADAFRUIT_IO_USERNAME = 'JIRS0129'
ADAFRUIT_IO_KEY = 'aio_XLzR28q51vuBwioB2o8Qab5qBrxe'

aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

try:
    temp = aio.feeds('temperatura')
except:
    temp = Feed(name = 'temperatura')
    temp = aio.create_feed(temp)

try:
    pres = aio.feeds('presion')
except:
    pres = Feed(name = 'presion')
    pres = aio.create_feed(pres)

try:
    humedaad = aio.feeds('humedaad')
except:
    humedad = Feed(name = 'humedaad')
    humedad = aio.create_feed(humedad)

try:
    calidad = aio.feeds('calidad')
except:
    calidad = Feed(name = 'calidad')
    calidad = aio.create_feed(calidad)

temperatura = 0
presion = 0
humedad = 0
qualite = 0

while(1):
    temperatura = uniform(-40.0, 140)
    aio.send_data(temp.key, temperatura)
    time.sleep(2)

    presion = uniform(100.0, 1000)
    aio.send_data(pres.key, presion)
    time.sleep(2)

    humdad = uniform(0.0, 100)
    aio.send_data(humedaad.key, humdad)
    time.sleep(2)

    qualite = uniform(0.0, 100)
    aio.send_data(calidad.key, qualite)
    time.sleep(2)
