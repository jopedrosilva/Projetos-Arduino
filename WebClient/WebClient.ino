#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char serverName[] = "192.168.1.101";
int serverPort = 80;

EthernetClient client;

void setup() {
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) == 0) {
    while(true);
  } else {
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    String incoming = Serial.readString();
    Serial.println(incoming);
    insertToDb(incoming);
  }
}

void insertToDb(String value) {
  String postData = "value=" + value;
  Serial.println(postData);
  
  Serial.println("connecting...");
  if (client.connect(serverName, serverPort)) {
    Serial.println("connected");
    client.print("POST /GerenciadorArduino/arduino.php");
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.println(postData);
    Serial.println("insert conplete");
  } else {
    Serial.println("connection failed");
  }

  client.stop();
}
