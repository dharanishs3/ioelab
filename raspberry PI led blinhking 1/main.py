import utime
import machine
LED_PIN=machine.Pin(17,machine.Pin.OUT)
while True:
    LED_PIN.value(1)
    utime.sleep(1)
    LED_PIN.value(0)
    utime.sleep(1)