from machine import Pin
import utime
import dht
dht_sensor=dht.DHT22(Pin(16))

while True:
    dht_sensor.measure()
    temp=dht_sensor.temperature()
    humd=dht_sensor.humidity()
    print("Temperature",temp,"c")
    print("humidity",humd,"%")
    utime.sleep(2)