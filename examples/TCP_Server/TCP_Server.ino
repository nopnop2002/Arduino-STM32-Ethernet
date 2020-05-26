/*
 * W5500 Ethernet Module TCP Server example.
 */

#include <SPI.h>
#include <Ethernet_STM.h>

#define SOCKET_PORT    9876             // You have to change

#if defined(W5100_ETHERNET_SHIELD)
  #define MODULE         "W5100"
#elif defined(W5200_ETHERNET_SHIELD)
  #define MODULE         "W5200"
#elif defined(W5500_ETHERNET_SHIELD)
  #define MODULE         "W5500"
#endif

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 
byte myIP[] = { 192, 168, 10, 190 };

EthernetServer server = EthernetServer(SOCKET_PORT);

void setup()
{
  delay(1000);Serial.begin(115200);
  Serial.print("Ethernet begin....");
  Ethernet.begin(mac,myIP);
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
//    Serial.println(Ethernet.localIP()[thisByte]);
    if (Ethernet.localIP()[thisByte] != myIP[thisByte] ) {
      Serial.println("fail....");
      while (1) {}
    }
  }
  Serial.println("ok....");
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  server.begin();
  Serial.println("Server Start. Wait for Client");
}

void loop()
{
  size_t size;
  EthernetClient client;
  
  if (client = server.available()) {
    while((size = client.available()) > 0) {
//      size = client.available();
      Serial.print("["+String(MODULE)+" Socket Server]Receive size=");
      Serial.println(size);
      char* rmsg = (char*)malloc(size);
      char* smsg = (char*)malloc(size);
      memset(smsg,0,sizeof(smsg));
      size = client.read((uint8_t *)rmsg,size);
      for (int i=0; i< size; i++){
        if(isalpha(rmsg[i])) {
          smsg[i] = toupper(rmsg[i]);
        } else {
          smsg[i] = rmsg[i];
        }
      } // end for
      Serial.write(rmsg,size);
      Serial.write("->");
      Serial.write(smsg,size);
      Serial.println("");

      free(rmsg);
      client.write(smsg,size);
      free(smsg);
    } // end while

    //wait for client disconnect
    while(1) {
      int r = client.connected();
//      Serial.println("r=" + String(r));
      if (r == 0) break;
    }
    Serial.println("client disconnect");
    client.stop();
  }
}
