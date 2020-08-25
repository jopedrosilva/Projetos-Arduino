#include <EtherCard.h>

static byte mymac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//static byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte Ethernet::buffer[700];
static uint32_t timer;

char mensagem[50];

const char website[] PROGMEM = "http://192.168.1.100/GerenciadorArduino";
static byte myip[] = { 192, 168, 1, 120 };
static byte gwip[] = {  192, 168, 1, 1 };

static void my_callback (byte status, word off, word len)
{
  Ethernet::buffer[off+len] = 0;
  Serial.print((const char*) Ethernet::buffer + off + 157);
}

void setup() {
  delay(100);
  Serial.begin(9600);
  Serial.println("Obtendo IP:");
  Serial.println(""+ether.begin(sizeof Ethernet::buffer, mymac, 53));
    if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
      Serial.println( "Falha ao acessar o controlador Ethernet");
    ether.staticSetup(myip, gwip);
    ether.printIp("IP: ", ether.myip);
    ether.printIp("Gatway: ", ether.gwip);
      ether.printIp("Servidor DNS: ", ether.dnsip);
      if (!ether.dnsLookup(website))
        Serial.println("Falha no DNS");
    ether.parseIp(ether.hisip, "http://192.168.1.100/GerenciadorArduino");
    ether.printIp("Servidor: ", ether.hisip);
    Serial.println(" ");
}

void loop() {
  ether.packetLoop(ether.packetReceive());
  if (millis() > timer){
    timer = millis() + 4000;
    ether.persistTcpConnection(true);
    sprintf(mensagem, "?inf=meupal");
    ether.browseUrl(PSTR("/arduino.php"), mensagem, website, my_callback);  
    Serial.println("vai tomar no teu cu!");
  }
   Serial.println("Galaaaaa");
   delay(500);
  
}
