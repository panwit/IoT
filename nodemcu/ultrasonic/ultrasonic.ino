void setup() {
  Serial.begin(9600);
  pinMode(D5, OUTPUT); // 4= Trig
  pinMode(D6, INPUT);  // 2= Echo
}

void loop() {
  digitalWrite(D5, HIGH);
  delayMicroseconds(10);
  digitalWrite(D5, LOW);

  int pulseWidth = pulseIn(D6, HIGH);
  Serial.print("Pulse Width: ");
  Serial.println(pulseWidth);
  
  long distance = pulseWidth/29/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);
}
