# Arduino-STM32-Ethernet
Arduino stm32 example for W5x00 ethernet modules.   
This project uses [this](https://github.com/arduino-libraries/Ethernet) library.

# Development Environment
[PlatformIO](https://github.com/platformio/platformio-core)

# Hardware requirements
- STM32F103 Development Board   
- ST-LINK/V2 or ST-LINK/V2.1 Module   
 You can use NECLEO board as ST-LINK/V2.1   
- USB-TTL Converter   
- External Voltage Regurator   
 BluePill or BlackPill board cannot supply too much current.   
 It is more stable when supplied from an external power source.   
 
# Selecting the Ethernet type controller (W5100, W5200 or W5500)
It is automatically selected inside the library.

# Wiring

|PHY|STM32||
|:-:|:-:|:-:|
|MOSI|PA7||
|MISO|PA6||
|SCLK|PA5||
|SS|PA4|*1|
|RST|RESET|*2|
|3.3V|3.3V|*3|
|GND|GND|*3|

(*1)  
You can specify any pin in platformio.ini.

(*2)  
Pull up when there is no RESET pin.

(*3)  
BluePill or BlackPill board cannot supply too much current.
It is more stable when supplied from an external power source.

```
                        +----------+          +----------+            +----------+
                        |BluePill  |          |ST-LINK   |            |HOST      |
                        |BlackPill |          |          +------------+          |
                        |          |----------|SWD-IO    |    USB     |          |
                        |          |----------|SWD-CLK   |            |          |
                        |          |----------|GND       +------------+          |
                        |          |----------|3V3       |            |          |
                        |          |          +----------+            |          |
                        |          |                                  |          |
                        |          |          +----------+            |          |
+----------+            |       PA9|----------|RX        |            |          |
|          |---(MOSI)---|       GND|----------|GND       |            |          |
|          |---(MISO)---|          |          |          |            |          |
|          |---(SCLK)---|          |          |          |            |          |
|          |---(SS)-----|          |          | USB-TTL  +------------+          |
|          |---(RESET)--|          |          |          |   USB      |          |
|          |---(GND)----|          |          |          |/dev/ttyUSB0|          |
|   PHY    |            |          |          |          +------------+          |
|          |            +----------+          |          |            |          |
|          |                                  |          |            |          |
|          |            +----------+          |          |            |          |
|          |---(GND)----|5v->3.3V  |---<5V>---|          |            |          |
|          |---(3.3V)---|Regulator |---<GND>--|          |            |          |
+----------+            +----------+          +----------+            +----------+
```


# Build
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd DhcpAddressPrinter
pio run -t upload -e bluepill_f103c8 && pio device monitor -b 115200 -p /dev/ttyUSB0
```

---

# Note
- I has not been tested on a real W5200 controller.   
- It cannot retrieve the Internal MAC address from WIZ550io.   

---

# More information
See [here](https://www.arduino.cc/en/Reference/Ethernet).

