import network
import urequests
import utime
import machine
import dht

# === Wi-Fi and ThingSpeak Setup ===
SSID = "Wokwi-GUEST"          # Built-in Wi-Fi in Wokwi
PASSWORD = ""                 # No password for Wokwi-GUEST
API_KEY = "1NIQXZV628HJA885"  # Replace with your key

# === DHT22 Sensor Setup ===
sensor = dht.DHT22(machine.Pin(16))   # Change to DHT11 if using that sensor

# === Wi-Fi Connection ===
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(SSID, PASSWORD)
    print("Connecting to Wi-Fi...", end="")
    while not wlan.isconnected():
        utime.sleep(0.5)
        print(".", end="")
    print("\nConnected to Wi-Fi!")
    print("IP Address:", wlan.ifconfig()[0])

# === Send Data to ThingSpeak ===
def send_data():
    try:
        sensor.measure()
        temp = sensor.temperature()
        humidity = sensor.humidity()
        print(f"Temperature: {temp:.1f}°C, Humidity: {humidity:.1f}%")

        url = f"https://api.thingspeak.com/update?api_key={API_KEY}&field1={temp}&field2={humidity}"
        response = urequests.get(url)
        response.close()
        print("Data sent to ThingSpeak!\n")
    except Exception as e:
        print("Error:", e)

# === Main Program ===
connect_wifi()
while True:
    send_data()
    utime.sleep(1)   # Upload every 15 seconds
