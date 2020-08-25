int valorSensorPIR = 0;
void setup() { 
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);

}

void loop() {
  valorSensorPIR = digitalRead(8);
  if (valorSensorPIR == 1) {
    digitalWrite(7, HIGH);
    digitalWrite(5, HIGH);
    Serial.println("DETECTADO");
  } else {
    digitalWrite(7, LOW);
    digitalWrite(5, LOW);
    Serial.println("---------");
  } 
  delay(200);
}
