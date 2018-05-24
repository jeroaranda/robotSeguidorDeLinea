void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,INPUT);
}

void loop() {
  digitalWrite(10,HIGH);
  analogWrite(8,100);
  analogWrite(9,0);
  delay(5000);
  
  analogWrite(8,0);
  analogWrite(9,50);
  delay(5000);
}
