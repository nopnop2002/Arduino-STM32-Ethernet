/*
 * W5500 Ethernet Module NTP Client example.
 * 
 * Get the time from a Network Time Protocol (NTP) time server
 * Demonstrates use of UDP sendPacket and ReceivePacket 
 * For more on NTP time servers and the messages needed to communicate with them, 
 * see http://en.wikipedia.org/wiki/Network_Time_Protocol
 */

#include <SPI.h>         
#include <Ethernet_STM.h>
#include <EthernetUdp.h>
#include <Dns.h>
#include <TimeLib.h>      // https://github.com/PaulStoffregen/Time

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

#if defined(W5100_ETHERNET_SHIELD)
  #define MODULE         "W5100"
#elif defined(W5200_ETHERNET_SHIELD)
  #define MODULE         "W5200"
#elif defined(W5500_ETHERNET_SHIELD)
  #define MODULE         "W5500"
#endif

// Your NTP Server
#define NTP_SERVER     "pool.ntp.org"

// Your local time zone
#define TIME_ZONE      9            

// local port to listen for UDP packets
#define LOCAL_PORT      8888

// NTP time stamp is in the first 48 bytes of the message
#define NTP_PACKET_SIZE 48

//buffer to hold incoming and outgoing packets 
byte packetBuffer[ NTP_PACKET_SIZE ];

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// Time of last packet transmission(ms)
unsigned long lastSendPacketTime = 0;

// Get Day of the week string [Sun,Mon....]
char * dow_char_EN(byte days) {
  char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  return dayOfWeek[days];
}

// Get Day of the week string (Japanese) [日曜,火曜....]
char * dow_char_JP(byte days) {
  char *dayOfWeek[] = {"日曜","月曜","火曜","水曜","木曜","金曜","土曜"};
  return dayOfWeek[days];
}

// Get Day of the week [0-Sunday, 1-Monday etc.]
uint8_t dow(unsigned long t) {
    return ((t / 86400) + 4) % 7;
}

void showTime(char * title, time_t timet, char * dow) {
   Serial.print(title);
   Serial.print(year(timet));
   Serial.print("/");
   Serial.print(month(timet));
   Serial.print("/");
   Serial.print(day(timet));
   Serial.print(" ");
   Serial.print(hour(timet));
   Serial.print(":");
   Serial.print(minute(timet));
   Serial.print(":");
   Serial.print(second(timet));
   Serial.print(" [");
   Serial.print(dow);
   Serial.println("]");

}

// send an NTP request to the time server at the given address 
void sendNTPpacket()
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 

  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:        
  Udp.beginPacket(NTP_SERVER, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket();

  return;
}

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

  // Resolving host names
  DNSClient dns;
  IPAddress ServerIP;
  dns.begin(Ethernet.dnsServerIP());
//  if(dns.getHostByName("ntp.jst.mfeed.ad.jp",ServerIP) == 1) {
  if(dns.getHostByName(NTP_SERVER,ServerIP) == 1) {
    Serial.println(F("dns lookup success"));
  } else {
    Serial.println(F("dns lookup failed"));
    while(1) { }
  }
    
  Udp.begin(LOCAL_PORT);
  Serial.println("Started listening for response.");
}

void loop()
{
  long now = millis();
  if (now - lastSendPacketTime > 5000) { // 5 seconds passed
    lastSendPacketTime = now;
    sendNTPpacket();
  }

  // wait to see if a reply is available
  if ( Udp.parsePacket() ) {  
    Serial.println("\n["+String(MODULE)+"] NTP Client");

    // We've received a packet, read the data from it
    Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);               

    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;     
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;  
    // print Unix time:
    Serial.print("Unix time = ");
    Serial.println(epoch);                               

#if 0
    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');  
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':'); 
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch %60); // print the second
#endif

    // Greenwich Mean Time
    uint8_t DayOfWeek = dow(epoch); 
    showTime("The UTC time is ", epoch, dow_char_EN(DayOfWeek));

    if (TIME_ZONE != 0) {
      // Local Time
      DayOfWeek = dow(epoch + (TIME_ZONE * 60 * 60));
      showTime("The LOCAL time is ", epoch + (TIME_ZONE * 60 * 60), dow_char_JP(DayOfWeek));
    }    
  }
}
