#define pinBuzzer 7
#define pinLDR A0
#define nivelLuz 970

void setup() {
   pinMode(pinBuzzer, OUTPUT);
   Serial.begin(9600);

}

void loop() {
  int valorLDR = analogRead(A0);

      if(valorLDR<820){
         String incoming = "Ligada";
         Serial.println(incoming);
         //insertToDb(incoming);  
      } else {
         String incoming = "Desligada";
         Serial.println(incoming);
         //insertToDb(incoming);
      }

      delay(1000);
}
