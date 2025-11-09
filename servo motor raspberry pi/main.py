from machine import Pin, PWM
from time import sleep

servo = PWM(Pin(15))
servo.freq(50)  # 50Hz PWM for servo

def set_angle(angle):
    # Map 0–180° → duty range for standard servo
    duty = int((angle / 180) * (8000 - 1500) + 1500)
    servo.duty_u16(duty)
    sleep(0.5)

while True:
    set_angle(0)
    sleep(1)
    set_angle(90)
    sleep(1)
    set_angle(180)
    sleep(1)
