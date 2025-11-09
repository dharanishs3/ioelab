#define sensorPin A0
#define sensorPower 7
#define LED_PIN 8

void setup() {
  pinMode(sensorPower, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Analog output : ");
  int val = readSensor();
  Serial.println(val);

  if (val > 1000) {
    Serial.println("Low moisture detected! Water the plants");
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(1000);
}

int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  int val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}
