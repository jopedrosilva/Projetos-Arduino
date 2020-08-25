#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(2, 3);
String page="http://10.0.1.4:80/GerenciadorArduino/arduino.php?inf=leydeamor";
void setup()
{
  gprsSerial.begin(2400);
  Serial.begin(9600);

  Serial.println("Config SIM900...");
  delay(1000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"algar.br\"");
  delay(1000);
  toSerial();


   // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"USER\",\"ALGAR\"");
  delay(1000);
  toSerial();

   // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"PWD\",\"1212\"");
  delay(1000);
  toSerial();

  // bearer settings
  
}


void loop()
{
 gprsSerial.println("AT+SAPBR=1,1");
  delay(1000);
  toSerial();
  
  gprsSerial.println("AT+SAPBR=2,1");
  delay(1000);
  toSerial();
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(1000); 
   toSerial();

   gprsSerial.println("AT+HTTPPARA=\"CID\",1");
   delay(1000); 
   toSerial();

   // set http param value
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://tcc-gsm.000webhostapp.com/poste/sinais.php?corrente=1.1111|1.1111|1.1111\"");
   delay(1000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(1000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("AT+SAPBR=0,1");
  delay(1000);
  toSerial();

   gprsSerial.println("");
   delay(1000);
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}
