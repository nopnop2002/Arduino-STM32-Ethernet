/*
  * W5500 Ethernet Module TCP Client example.
  */

#include <SPI.h>
#include <Ethernet_STM.h>

#define INTERVAL       5000
#define SOCKET_HOST    "192.168.10.11"  // You have to change
#define SOCKET_PORT    9876             // You have to change
#define TIME_OUT       10000

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

#if defined(W5100_ETHERNET_SHIELD)
  #define MODULE         "W5100"
#elif defined(W5200_ETHERNET_SHIELD)
  #define MODULE         "W5200"
#elif defined(W5500_ETHERNET_SHIELD)
  #define MODULE         "W5500"
#endif

EthernetClient client;

unsigned long nextMillis;

void setup() {
 
  delay(1000);Serial.begin(115200);
  Serial.print("Ethernet begin....");
  if (!Ethernet.begin(mac) ) {
    Serial.println("faild to begin");
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
  nextMillis = millis();
}


void loop() {
  static int num = 0;
  char smsg[30];
  char rmsg[30];
  int rflag;
  unsigned long timeout;
  unsigned long now;
  
  now = millis();
  if ( long(now - nextMillis) > 0) {
    nextMillis = millis() + INTERVAL;
    Serial.print("Client connect....");
    if (!client.connect(SOCKET_HOST, SOCKET_PORT)) {
      Serial.println("failed");
    } else {
      Serial.println("ok");
      sprintf(smsg,"data from arduino %05d",num);
      num++;
      client.write(smsg, strlen(smsg));

      // wait for responce
      rflag = 1;
      timeout = millis();
      while(client.available() == 0) {
        now = millis();
//        Serial.println("now="+String(now));
//        Serial.println("timeout="+String(timeout));
        if (long(now - timeout) > TIME_OUT) {
          rflag = 0;
        }
      } // end while

      Serial.print("Server response....");
      if (rflag == 0) {
        Serial.println("failed");
      } else {
        Serial.println("ok");
        int size;
        while((size = client.available()) > 0) {
          Serial.print("["+String(MODULE)+" Socket Client]Receive Size=");
          Serial.println(size);
          size = client.read((uint8_t *)rmsg,size);
          Serial.write((uint8_t *)smsg,size);
          Serial.write("->");
          Serial.write((uint8_t *)rmsg,size);
          Serial.println("");
        } // end while
      }

      //disconnect client
      Serial.println("Client disconnect");
      client.stop();
    } // end if
  } // end if
}
