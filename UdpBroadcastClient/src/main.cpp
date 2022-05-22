/*
 * W5500 Ethernet Module UDP Broadcast Client example.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

// local port to listen for UDP packets
#define LOCAL_PORT      8888

// remote port to send for UDP packets
#define REMOTE_PORT     9876

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

void loop() {
  static unsigned long lastSendPacketTime = 0;
  unsigned long now = millis();
  if (now < lastSendPacketTime) lastSendPacketTime = 0;
  if (now - lastSendPacketTime > 1000) { // 5 seconds passed
    lastSendPacketTime = now;
    Udp.beginPacket("255.255.255.255", REMOTE_PORT);
    byte packetBuffer[64];
    sprintf((char *)packetBuffer, "Hello World %ld", millis());
    size_t packetSize = strlen((char*)packetBuffer);
    Udp.write(packetBuffer, packetSize);
    Udp.endPacket();
  }
}
