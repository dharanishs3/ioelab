from machine import Pin
import utime

trigger=Pin(2,Pin.OUT)
echo=Pin(3,Pin.IN)

def get_distance():
    trigger.value(1)
    utime.sleep_us(10)
    trigger.value(0)

    while echo.value()==0:
        signaloff=utime.ticks_us()
    
    while echo.value()==1:
        signalon=utime.ticks_us()
    
    timeduration=signalon-signaloff
    dist=(timeduration*0.034)/2
    return int(dist)

while True:
    distance=get_distance()
    print("Distance :",distance,"cm")
    utime.sleep(5)