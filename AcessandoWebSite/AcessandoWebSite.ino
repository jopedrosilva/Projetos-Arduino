#include <bufferfiller.h>
#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>
#include <stash.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
byte Ethernet::buffer[700];
static uint32_t timer;

char mensagem[50];

const char website[] PROGMEM = "10.0.2.103";
static byte myip[] = { 10,0,2,200 };
static byte gwip[] = { 10,0,2,2 };

static void mycallback (byte status, word off, word len) {
  Ethernet::buffer[off+len] = 0;
  Serial.print((const char*) Ethernet::buffer + off + 157);  
}

void setup() {
  delay(1000);
  Serial.begin(57600);
  Serial.println("Obtendo IP:");
  if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0)
    Serial.println("Falha ao acessar o controlador Ethernet");
  ether.staticSetup(myip, gwip);
  ether.printIp("IP: ", ether.myip);
  ether.printIp("Gatway: ", ether.gwip);
    ether.printIp("Servidor DNS: ", ether.dnsip);
    if (!ether.dnsLookup(website))
      Serial.println("Falha no DNS");
    ether.parseIp(ether.hisip, "10.0.2.103");
    ether.printIp("Servidor: ", ether.hisip);
    Serial.println(" ");  

}

void loop() {
  ether.packetLoop(ether.packetReceive());
  if (millis() > timer) {
    timer = millis() + 4000;
    ether.persistTcpConnection(true);
    sprintf(mensagem, "?inf=oi");
    ether.browseUrl(PSTR("/arduino.php"), mensagem, website, mycallback);  
  }
}
