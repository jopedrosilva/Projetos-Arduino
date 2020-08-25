void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, HIGH);
  delay(2000);
  digitalWrite(10, LOW);
  delay(2000);
}
