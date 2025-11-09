const int sensorPin=A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Temprature Sensor Interfacing Starting..");

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue=analogRead(sensorPin);
  float voltage=sensorValue*(5.0/1023.0);
  float temp=voltage*100.0;
  Serial.print(("Temprature"));
  Serial.print(temp);
  Serial.println("°c");
  delay(1000);

}
