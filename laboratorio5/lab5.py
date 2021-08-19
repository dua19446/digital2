from Adafruit_IO import Client, RequestError, Feed
ADAFRUIT_IO_KEY = "aio_nmSa16ffaXfWBS4sdME2dOamGIYk"
ADAFRUIT_IO_USERNAME = "AlexD10"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

sr1_feed = aio.feeds('sensor-1')
aio.send_data(sr1_feed.key, 12)
sr1_data = aio.receive(sr1_feed.key)
print(f'analog signal: {sr1_data.value}')

sr2_feed = aio.feeds('sensor-2')
aio.send_data(sr2_feed.key, 56)
sr2_data = aio.receive(sr2_feed.key)
print(f'digital signal: {sr2_data.value}')
