#include "DHT.h"

#define DHTPIN 9
#define DHTTYPE DHT22
#define GAS_SENSOR A0
#define BUZZER 7
#define LED 6

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(GAS_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("System Initialized... DHT22 + MQ2");
  delay(2000);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gasValue = analogRead(GAS_SENSOR);

  Serial.print("Temp: "); Serial.print(temperature); Serial.print(" °C   ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print(" %   ");
  Serial.print(" Gas: "); Serial.println(gasValue);

  if (temperature > 40 || gasValue > 500) {
    tone(7, 262, 250); // Plays 262Hz tone for 0.250 seconds
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);
    Serial.println("ALERT! Unsafe conditions detected!");
  } else {
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);
    Serial.println("Conditions are safe.");
  }

  delay(1000);
}
