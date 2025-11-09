from machine import Pin
import time

# Define the LED and Button pins
led = Pin(15, Pin.OUT)              # LED connected to GPIO15
button = Pin(14, Pin.IN, Pin.PULL_UP)  # Button connected to GPIO14 with internal pull-up resistor

while True:
    if button.value() == 0:   # Button pressed (active LOW)
        led.value(1)          # Turn ON LED
    else:
        led.value(0)          # Turn OFF LED
    time.sleep(0.5)           # Small delay for debounce
