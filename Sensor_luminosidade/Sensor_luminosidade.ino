#include <SPI.h>
#include <Ethernet.h>
#define pinBuzzer 7
#define pinLDR A0
#define nivelLuz 970

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char serverName[] = "192.168.1.102";
int serverPort = 80;

String readString;

//=========================
//byte ip[] = { 192, 168, 1, 177 };

//=========================
EthernetServer servidor(80);

EthernetClient client;

void setup() {
  pinMode(pinBuzzer, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) == 0) {
    while(true);
  } else {
    Serial.println(Ethernet.localIP());
     Ethernet.begin(mac, Ethernet.localIP());
     servidor.begin();
  }
  delay(1000);
}

void loop() {
  //====================================
  int valorLDR = analogRead(A0);

  if(valorLDR<820){
    String incoming = "Ligada";
    Serial.println(incoming);
    insertToDb(incoming);  
  } else {
    String incoming = "Desligada";
    Serial.println(incoming);
    insertToDb(incoming);
  }

  delay(500);
  
  EthernetClient cliente = servidor.available();
 
  if (cliente) {
    while (cliente.connected()) {
       
      if (cliente.available()) {
        char c = cliente.read();

        if (readString.length() < 100) {
          readString += c;
        }

        if (c == '\n') {
          cliente.println("HTTP/1.1 200 OK");
          cliente.println("Content-Type: text/html");
          cliente.println();

          cliente.println("<HTML>");
          cliente.println("<BODY>");
          cliente.println("<CENTER><H1>Servidor Arduino</H1></CENTER>");
          cliente.println("<CENTER><a href=\"/?led_ligar\"><button>LIGAR</button></a><a href=\"/?led_desligar\"><button>DESLIGAR</button></a></CENTER>");
          cliente.println("</BODY>");
          cliente.println("</HTML>");

          delay(1);
          cliente.stop();

          if (readString.indexOf("?led_ligar") > 0) {
            digitalWrite(8, LOW);
            delay(500);
          } else {
            if (readString.indexOf("?led_desligar") > 0) {
              digitalWrite(8, HIGH);
              delay(500);
            }
          }
          
          readString = "";
        }
      }
    }
  }
  //====================================
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
