#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHT_PIN 12
#define DHT_TYPE DHT22
#define PULSE_PIN 35  // Potentiometer signal pin

// WiFi + MQTT
const char *ssid = "Wokwi-GUEST";
const char *password = "";
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_PORT 1883
#define MQTT_TOPIC_HR "/heartRate"
#define MQTT_TOPIC_TEMP "/tempValue"
#define MQTT_TOPIC_HUM "/humValue"

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT_TYPE);

void connectToWiFi();
void reconnect();

void setup() {
  Serial.begin(115200);
  Serial.println(" ESP32 Health Monitor Starting...");
  dht.begin();
  connectToWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT read failed!");
    delay(2000);
    return;
  }

  int pulseValue = analogRead(PULSE_PIN);
  float voltage = pulseValue * (3.3 / 4095.0);
  int heartRate = (voltage / 3.3) * 675; // Simulated formula

  Serial.printf("Heart: %d BPM | %.1f°C | %.1f%%\n",
                heartRate, temperature, humidity);

  client.publish(MQTT_TOPIC_HR, String(heartRate).c_str());
  client.publish(MQTT_TOPIC_TEMP, String(temperature).c_str());
  client.publish(MQTT_TOPIC_HUM, String(humidity).c_str());

  Serial.println("MQTT Data Sent\n");
  delay(2000);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("esp32_health_monitor")) {
      Serial.println("Connected ");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" — retrying in 5s");
      delay(5000);
    }
  }
}
