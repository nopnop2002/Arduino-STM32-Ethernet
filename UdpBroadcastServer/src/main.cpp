/*
 * W5500 Ethernet Module UDP Broadcast Server example.
 */

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

// local port to listen for UDP packets
#define LOCAL_PORT      9876

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// Time of last packet transmission(ms)
unsigned long lastSendPacketTime = 0;

void setup() {
  // Open serial communications and wait for port to open:
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // You can use Ethernet.init(pin) to configure the CS pin
#if defined GPIO_CS
  Serial.print("GPIO_CS=");
  Serial.println(GPIO_CS);
  Ethernet.init(GPIO_CS);
#else
  Ethernet.init(PA4);
#endif


  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100) {
    Serial.println("W5100 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5200) {
    Serial.println("W5200 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5500) {
    Serial.println("W5500 Ethernet controller detected.");
  }
  
  // print your local IP address:
  Serial.print("Ethernet.localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Ethernet.subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Ethernet.gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("Ethernet.dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  Udp.begin(LOCAL_PORT);
}

String ipToString(IPAddress ipadr){
    String result = "";

    result += String(ipadr[0], 10);
    result += ".";
    result += String(ipadr[1], 10);
    result += ".";
    result += String(ipadr[2], 10);
    result += ".";
    result += String(ipadr[3], 10);

    return result;
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    String ip = ipToString(Udp.remoteIP());
    char buf[20];
    ip.toCharArray(buf, sizeof(buf));

    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP(), Udp.remotePort());
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, ipToString(Udp.remoteIP()), Udp.remotePort());
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, buf, Udp.remotePort());
    char rmsg[128];
    int len = Udp.read(rmsg, sizeof(rmsg));
    if (len > 0) {
      rmsg[len] = 0;
      Serial.printf("UDP packet contents: %s\n", rmsg);
    }
  }
}

