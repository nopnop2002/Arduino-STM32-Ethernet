/*
 modified 12 Aug 2013
 by Soohwan Kim (suhwan@wiznet.co.kr)
*/
#include "Ethernet_STM.h"
#include "Dhcp.h"

// XXX: don't make assumptions about the value of MAX_SOCK_NUM.
uint8_t EthernetClass::_state[MAX_SOCK_NUM] = { 0, };
uint16_t EthernetClass::_server_port[MAX_SOCK_NUM] = { 0, };

DhcpClass _dhcp;

#if defined(WIZ550io_WITH_MACADDRESS)
int EthernetClass::begin(int chip_select)
{
  byte mac_address[6] ={0,};

  // Initialise the basic info
  W5100.init(chip_select);
  W5100.setIPAddress(IPAddress(0,0,0,0).raw_address());
  W5100.getMACAddress(mac_address);
Serial.println("WIZ550io_WITH_MACADDRESS MACAddress is");
for(int i = 0; i < 6; i++) {
	Serial.print(mac_address[i],HEX);
	Serial.print(" ");
}
Serial.println("");

  // Now try to get our config info from a DHCP server
  int ret = _dhcp.beginWithDHCP(mac_address);
  if(ret == 1)
  {
    // We've successfully found a DHCP server and got our configuration info, so set things
    // accordingly
    W5100.setIPAddress(_dhcp.getLocalIp().raw_address());
    W5100.setGatewayIp(_dhcp.getGatewayIp().raw_address());
    W5100.setSubnetMask(_dhcp.getSubnetMask().raw_address());
    _dnsServerAddress = _dhcp.getDnsServerIp();
  }

  return ret;
}

void EthernetClass::begin(IPAddress local_ip, int chip_select)
{
  // Assume the DNS server will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress dns_server = local_ip;
  dns_server[3] = 1;
  begin(local_ip, dns_server, chip_select);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress dns_server, int chip_select)
{
  // Assume the gateway will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress gateway = local_ip;
  gateway[3] = 1;
  begin(local_ip, dns_server, gateway, chip_select);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, int chip_select)
{
  IPAddress subnet(255, 255, 255, 0);
  begin(local_ip, dns_server, gateway, subnet, chip_select);
}

void EthernetClass::begin(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet, int chip_select)
{
  W5100.init(chip_select);
  W5100.setIPAddress(local_ip.raw_address());
  W5100.setGatewayIp(gateway.raw_address());
  W5100.setSubnetMask(subnet.raw_address());
  _dnsServerAddress = dns_server;
}
#else
int EthernetClass::begin(uint8_t *mac_address, int chip_select)
{
  // Initialise the basic info
  W5100.init(chip_select);
  W5100.setMACAddress(mac_address);
  W5100.setIPAddress(IPAddress(0,0,0,0).raw_address());

  // Now try to get our config info from a DHCP server
  int ret = _dhcp.beginWithDHCP(mac_address);
  if(ret == 1)
  {
    // We've successfully found a DHCP server and got our configuration info, so set things
    // accordingly
    W5100.setIPAddress(_dhcp.getLocalIp().raw_address());
    W5100.setGatewayIp(_dhcp.getGatewayIp().raw_address());
    W5100.setSubnetMask(_dhcp.getSubnetMask().raw_address());
    _dnsServerAddress = _dhcp.getDnsServerIp();
  }

  return ret;
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, int chip_select)
{
  // Assume the DNS server will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress dns_server = local_ip;
  dns_server[3] = 1;
  begin(mac_address, local_ip, dns_server, chip_select);
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, int chip_select)
{
  // Assume the gateway will be the machine on the same network as the local IP
  // but with last octet being '1'
  IPAddress gateway = local_ip;
  gateway[3] = 1;
  begin(mac_address, local_ip, dns_server, gateway, chip_select);
}

void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, int chip_select)
{
  IPAddress subnet(255, 255, 255, 0);
  begin(mac_address, local_ip, dns_server, gateway, subnet, chip_select);
}

void EthernetClass::begin(uint8_t *mac, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet, int chip_select)
{
  W5100.init(chip_select);
  W5100.setMACAddress(mac);
  W5100.setIPAddress(local_ip.raw_address());
  W5100.setGatewayIp(gateway.raw_address());
  W5100.setSubnetMask(subnet.raw_address());
  _dnsServerAddress = dns_server;
}

#endif

int EthernetClass::maintain(){
  int rc = DHCP_CHECK_NONE;
  //if(_dhcp != NULL){
    //we have a pointer to dhcp, use it
    rc = _dhcp.checkLease();
    switch ( rc ){
      case DHCP_CHECK_NONE:
        //nothing done
        break;
      case DHCP_CHECK_RENEW_OK:
      case DHCP_CHECK_REBIND_OK:
        //we might have got a new IP.
        W5100.setIPAddress(_dhcp.getLocalIp().raw_address());
        W5100.setGatewayIp(_dhcp.getGatewayIp().raw_address());
        W5100.setSubnetMask(_dhcp.getSubnetMask().raw_address());
        _dnsServerAddress = _dhcp.getDnsServerIp();
        break;
      default:
        //this is actually a error, it will retry though
        break;
    }
  //}
  return rc;
}

IPAddress EthernetClass::localIP()
{
  IPAddress ret;
  W5100.getIPAddress(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::subnetMask()
{
  IPAddress ret;
  W5100.getSubnetMask(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::gatewayIP()
{
  IPAddress ret;
  W5100.getGatewayIp(ret.raw_address());
  return ret;
}

IPAddress EthernetClass::dnsServerIP()
{
  return _dnsServerAddress;
}

EthernetClass Ethernet;
