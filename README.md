# Arduino-STM32-Ethernet
Arduino stm32 support files for W5x00 ethernet modules.   
__This library is no longer going to be used, since the [official Arduino library](https://github.com/arduino-libraries/Ethernet) has been updated and works great.__

I ported from [here](https://github.com/Serasidis/Ethernet_STM).

Arduino_Core_STM32 supports SPI library, but only works in Transaction SPI Mode.

- Legacy SPI Mode   
SPI speed depends on the CPU frequency.
```
SPI.begin()
SPI.setClockDivider(divider)
SPI.setDataMode(mode)
SPI.setBitOrder(order)
SPI.transfer(data);
```

- Transaction SPI Mode   
SPI speed NOT depends on the CPU frequency.
```
SPI.begin()
SPI.beginTransaction(SPISettings(speed, order, mode))
SPI.transfer(data);
SPI.endTransaction()
```

This repository works with Transaction SPI Mode.

---

# W5x00 ethernet library for STM32 micro-controllers
That library has been ported from the **WIZnet WIZ_Ethernet_Library**, to STM32 microcontrollers.   
The library supports **W5100** and **W5500** Ethernet controllers.    
The source code has been modified to support the **W5200** too, but has not been tested on a real W5200 controller.   

Ported to STM32F103 on 23 Aug 2015 by **Vassilis Serasidis**

---

# Selecting the Ethernet type controller (W5100, W5200 or W5500)

For selecting among those tree chips edit the file:
`Arduino-STM32-Ethernet\src\utility\w5100.h`
and comment-out only the line with the chip you want to use.



By default the **W5500** ethernet controller is selected.


```
//#define W5100_ETHERNET_SHIELD // Arduino Ethenret Shield and Compatibles ...
//#define W5200_ETHERNET_SHIELD // WIZ820io, W5200 Ethernet Shield 
#define W5500_ETHERNET_SHIELD   // WIZ550io, ioShield series of WIZnet
```
If you edit the **w5100.h** file, save it and re-compile your sketch.

---

# Tested boards

|Board|MOSI|MISO|SCK|SS(*1)|RST(*2)|SerialTX|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|Arduino UNO|D11|D12|D13|D10|RESET|D1|
|Arduino MEGA|D51|D50|D52|D53|RESET|D1|
|Arduno DUE|A.26|A.25|A.27|D10|RESET|D1|
|STM32F103|PA7|PA6|PA5|PA4|RESET|PA9|
|STM32F303|PA7|PA6|PA5|PA4|RESET|PA9|
|STM32F401|PA7|PA6|PA5|PA4|RESET|PA9|
|STM32F411|PA7|PA6|PA5|PA4|RESET|PA9|
|FEATHER_F405|PB15|PB14|PB13|PA15|RESET|PB10|
|BLACK_F407|PB5|PB4|PB3|PB7(*3)|PullUp|PB10|
|BLUE_F407VE_Mini|PB15|PB14|PB13|PB12|PullUp|PB10|
|DIYMORE_F407VGT|PB5|PB4|PB3|PB6|PullUp|PB10|

(*1)You can change SS pin.
```
int EthernetClass::begin(uint8_t *mac_address, int chip_select)
void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, int chip_select)
void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, int chip_select)
void EthernetClass::begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, int chip_select)
```

(*2)Pull up when there is no RESET pin.

(*3)This port cannot be used because it is used with the onboard NRF24 connector.
You need to specify a different port.

__Keep jumper cables as short as possible.__

__STM32 uses [this](https://github.com/stm32duino/Arduino_Core_STM32) core library.__

__STM32 and DUE is NOT 5V tolerant.__

---

# API & Examples
See [here](https://www.arduino.cc/en/reference/ethernet).

---

# Note
- I has not been tested on a real W5200 controller.   
- It cannot retrieve the Internal MAC address from WIZ550io.   

---

# More information
See [here](https://github.com/Serasidis/Ethernet_STM).

