# Arduino-STM32-Ethernet
Arduino stm32 example for W5x00 ethernet modules.   

# W5x00 ethernet library for arduino
This project uses [this](https://github.com/arduino-libraries/Ethernet) library.

# Selecting the Ethernet type controller (W5100, W5200 or W5500)
It is automatically selected inside the library.

# Wiring

|PHY|STM32|
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
STM32 development board cannot supply too much current.
It is more stable when supplied from an external power source.

```
+----------+            +----------+          +----------+
|          |---(MOSI)---|          |          |          |
|          |---(MISO)---|          |---<5V>---|          |
|          |---(SCLK)---|  STM32   |          |          |
|          |---(SS)-----| DEV BOARD|          |          |
|          |---(RESET)--|          |---<GND>--|  POWER   |
|   PHY    |---(GND)----|          |          |  SOURCE  |
|          |            +----------+          |          |
|          |                                  |          |
|          |            +----------+          |          |
|          |---(GND)----| 5v->3,3V |---<5V>---|          |
|          |---(3.3V)---| Regulator|---<GND>--|          |
+----------+            +----------+          +----------+
```


# API & Examples
See [here](https://www.arduino.cc/en/reference/ethernet).

---

# Note
- I has not been tested on a real W5200 controller.   
- It cannot retrieve the Internal MAC address from WIZ550io.   

---

# More information
See [here](https://github.com/Serasidis/Ethernet_STM).

