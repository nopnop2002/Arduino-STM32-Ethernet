/*
 * W5500 Ethernet Module DHCP-based IP printer.
 */

#include <SPI.h>         
#include <Ethernet_STM.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

void setup() {
   
  delay(1000);Serial.begin(115200);
#if defined WIZ550io_WITH_MACADDRESS
  Serial.print("WIZ550io Ethernet begin....");
  if (!Ethernet.begin() ) {
#else
  Serial.print("W5500 Ethernet begin....");
  //if (!Ethernet.begin(mac, PA4) ) {  // Specify Chip Select
  if (!Ethernet.begin(mac) ) { // Default ChipSelect
#endif
    Serial.println("Ethetnet begin fail");
    while(1) {}
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

  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    if (thisByte != 3) Serial.print("-");
  }

#if defined WIZ550io_WITH_MACADDRESS
  uint8_t MACaddress[6]; // array for mac address
  W5100.getMACAddress(MACaddress);
  Serial.print("WIZ550 mac Address is ");
  for(int i = 0; i < 6; i++) {
    if (MACaddress[i] < 0x10) Serial.print("0");
    Serial.print(MACaddress[i],HEX);
    if (i != 5) Serial.print("-");
  }
  Serial.println("");
#endif

}

void loop() {
}
