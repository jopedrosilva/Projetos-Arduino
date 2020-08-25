#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 177 };

EthernetServer servidor(80);

String readString;

void setup() {
  pinMode(8, OUTPUT);
  Ethernet.begin(mac, ip);
  servidor.begin();
}

void loop() {
  
  
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
          cliente.println("<CENTER><H1>Servidor</H1></CENTER>");
          cliente.println("<a href=\"/?led_ligar\"><button>LIGAR</button></a><a href=\"/?led_desligar\"><button>DESLIGAR</button></a>");
          cliente.println("<a href=\"http://http://169.254.211.154/GerenciadorArduino/index.php\"><button>Link</button></a><a href=\"/?led_desligar\"><button>DESLIGAR</button></a>");
          //client.println("https://www.charllesrocha.com.br/lucas_testes/inserir.php?temp=555");
          //client.println("Host: <a href='http://www.charllesrocha.com.br'); target='_blank'>www.charllesrocha.com.br</a>");
          cliente.println("</BODY>");
          cliente.println("</HTML>");

          delay(1);
          cliente.stop();

          if (readString.indexOf("?led_ligar") > 0) {
            digitalWrite(8, LOW);
          } else {
            if (readString.indexOf("?led_desligar") > 0) {
              digitalWrite(8, HIGH);
            }
          }
          
          readString = "";
        }
      }
    }
  }
}
