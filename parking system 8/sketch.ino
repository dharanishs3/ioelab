# define trigger 9
# define echo 10
# define led_red 7
#define led_green 6
void setup() {
  // put your setup code here, to run once:
  pinMode(trigger,OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration;
  int distance ;
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration=pulseIn(echo,HIGH);
  distance=duration*0.034/2;

  Serial.print("Distance :");
  Serial.print(distance);
Serial.println(( "cm"));
if(distance >0 && distance <10){
  digitalWrite(led_red, HIGH);
  digitalWrite(led_green, LOW);
}
else{
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, HIGH);
}
delay(500);
}
