/*
 modified 12 Aug 2013
 by Soohwan Kim (suhwan@wiznet.co.kr)
*/
#ifndef ethernet_h
#define ethernet_h

#include <inttypes.h>
#include "utility/w5100.h"
#include "IPAddress.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dhcp.h"



class EthernetClass {
private:
  IPAddress _dnsServerAddress;
  //DhcpClass* _dhcp;
public:
  static uint8_t _state[MAX_SOCK_NUM];
  static uint16_t _server_port[MAX_SOCK_NUM];

#if defined(WIZ550io_WITH_MACADDRESS)
  // Initialize function when use the ioShield serise (included WIZ550io)
  // WIZ550io has a MAC address which is written after reset.
  // Default IP, Gateway and subnet address are also writen.
  // so, It needs some initial time. please refer WIZ550io Datasheet in details.
  int begin(int chip_select=SS);
  void begin(IPAddress local_ip, int chip_select=SS);
  void begin(IPAddress local_ip, IPAddress dns_server, int chip_select=SS);
  void begin(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, int chip_select=SS);
  void begin(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet, int chip_select=SS);
#else
  // Initialize the Ethernet shield to use the provided MAC address and gain the rest of the
  // configuration through DHCP.
  // Returns 0 if the DHCP configuration failed, and 1 if it succeeded
  int begin(uint8_t *mac_address, int chip_select=SS);
  void begin(uint8_t *mac_address, IPAddress local_ip, int chip_select=SS);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, int chip_select=SS);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, int chip_select=SS);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet, int chip_select=SS);

#endif
  
  int maintain();

  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

  friend class EthernetClient;
  friend class EthernetServer;
};

extern EthernetClass Ethernet;

#endif
