#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {10,0,2,200};                         //IP DO ARDUINO (WEB CLIENT)
byte servidor[] = {10,0,2,103};                   //IP DO SERVIDOR 

EthernetClient cliente;

void setup() {   
            Serial.begin(9600);  
            Ethernet.begin(mac, ip);
         }

void loop() {

 if (cliente.connect(servidor, 80))  //Se o arduino se conectar ao servidor
{
     cliente.print("GET http://10.0.2.103:80/GerenciadorArduino/arduino.php?inf=oi\r\nHost: 10.0.2.103\r\n\r\n"); //Envia  $_GET['a'] = 2;
     cliente.print(" HTTP/1.1");
     cliente.stop();
     Serial.println("Informação enviada com sucesso!"); 
} 
else {Serial.println("Falha na conexão");}
delay(5000);
}
