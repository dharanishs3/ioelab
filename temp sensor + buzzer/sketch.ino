const int tempSensorPin = A0;  // Use analog pin A0 for LM35
const int buzzerPin = 8;
const float thresholdTemp = 40.0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // int analogValue = analogRead(tempSensorPin);            // Read analog input
  // float voltage = (analogValue * 5.0) / 1023.0;           // Convert to voltage
  // float temperature = voltage * 100.0;                    // LM35: 10mV per °C
  const float BETA = 3950; // should match the Beta Coefficient of the thermistor
  int analogValue = analogRead(A0);
  float temperature = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Check threshold
  if (temperature > thresholdTemp) {
    digitalWrite(buzzerPin, HIGH); 
    tone(8, 262, 250); // Plays 262Hz tone for 0.250 seconds
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn buzzer OFF
    digitalWrite(9, LOW); // Turn buzzer ON
  }

  delay(1000);
}
