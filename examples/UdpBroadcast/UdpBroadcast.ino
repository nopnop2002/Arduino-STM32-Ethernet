/*
 * W5500 Ethernet Module UDP Broadcast example.
 */

#include <SPI.h>         
#include <Ethernet_STM.h>
#include <EthernetUdp.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

#if defined(W5100_ETHERNET_SHIELD)
  #define MODULE         "W5100"
#elif defined(W5200_ETHERNET_SHIELD)
  #define MODULE         "W5200"
#elif defined(W5500_ETHERNET_SHIELD)
  #define MODULE         "W5500"
#endif

// local port to listen for UDP packets
#define LOCAL_PORT      8888

// remote port to send for UDP packets
#define REMOTE_PORT     9876

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// Time of last packet transmission(ms)
unsigned long lastSendPacketTime = 0;


void setup() 
{
  delay(1000);Serial.begin(115200);
  Serial.print("Ethernet begin....");
  //if (!Ethernet.begin(mac, PA4) ) { // Specify Chip Select
  if (!Ethernet.begin(mac) ) { // Default ChipSelect
    Serial.println("Failed to configure Ethernet using DHCP");
    while(1) {}
  }
  Serial.println("ok");
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  Udp.begin(LOCAL_PORT);
}

void loop()
{
  long now = millis();
  if (now - lastSendPacketTime > 5000) { // 5 seconds passed
    lastSendPacketTime = now;
    Udp.beginPacket("255.255.255.255", REMOTE_PORT);
    byte packetBuffer[64];
    sprintf((char *)packetBuffer, "Hello %s %d", MODULE, millis());
    size_t packetSize = strlen((char*)packetBuffer);
    Udp.write(packetBuffer, packetSize);
    Udp.endPacket();
  }
}
