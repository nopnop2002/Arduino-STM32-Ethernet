# Arduino-STM32-Ethernet
Arduino stm32 example for W5x00 ethernet modules.   
This project uses [this](https://github.com/arduino-libraries/Ethernet) library.


# Software requirements
PlatformIO will automatically install the required libraries according to the ini file.   
Great!   

# Platform IO installation
[PlatformIO](https://github.com/platformio/platformio-core)
```
$ python3 --version
Python 3.7.3

$ sudo apt install python3-pip python3-setuptools

$ python3 -m pip -V
pip 18.1 from /usr/lib/python3/dist-packages/pip (python 3.7)

The pip installed by apt is old, so update to the latest.
$ python3 -m pip install -U pip

$ python3 -m pip -V
pip 20.3.1 from /home/orangepi/.local/lib/python3.7/site-packages/pip (python 3.7)

Update wheels.
$ python3 -m pip install -U wheel

$ pip3 install -U platformio
```

# Hardware requirements
- STM32F103 Development Board   
- W5100/W5200/W5500 Ethernet Module   
 About $5 for aliexpress/eBay.   
 W5100 is for 5V only.   
 W5500 can be used at both 3.3V / 5V.   
- ST-LINK/V2 or ST-LINK/V2.1 Module   
 About $5 for aliexpress/eBay.   
 You can use NECLEO board as ST-LINK/V2.1   
- USB-TTL Converter   
 For Serial monitoring.   
- External Voltage Regurator   
 BluePill or BlackPill board cannot supply too much current.   
 It is more stable when supplied from an external power source.   
 AMS1117 is often used.   
 
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

- Supplied from ST-LINK
```
                        +----------+            +----------+            +----------+
                        |BluePill  |            |ST-LINK   |            |HOST      |
                        |BlackPill |            |          [------------]          |
                        |          |------------|SWD-IO    [    USB     ]          |
                        |          |------------|SWD-CLK   [------------]          |
                        |          |------------|GND       |            |          |
                        |          |------------|3V3       |            |          |
                        |          |            +----------+            |          |
                        |          |                                    |          |
                        |          |            +----------+            |          |
+----------+            |       PA9|------------|RX        |            |          |
|          |---(MOSI)---|       GND|------------|GND       |            |          |
|          |---(MISO)---|          |            |          |            |          |
|          |---(SCLK)---|          |            |          |            |          |
|          |---(SS)-----|          |            | USB-TTL  [------------]          |
|          |---(RESET)--|          |            |          [   USB      ]          |
|          |            |          |            |          [/dev/ttyUSB0]          |
|   PHY    |            |          |            |          [------------]          |
|          |            +----------+            |          |            |          |
|          |                                    |          |            |          |
|          |            +----------+            |          |            |          |
|          |---(3V3)----|5v->3.3V  |----(5V)----|          |            |          |
|          |---(GND)----|Regulator |----(GND)---|          |            |          |
+----------+            +----------+            +----------+            +----------+
```

- Supplied from USB
```
                        +----------+            +----------+            +----------+
                        |BluePill  |            |ST-LINK   |            |HOST      |
                        |BlackPill |            |          [------------]          |
                        |          |------------|SWD-IO    [    USB     ]          |
                        |          |------------|SWD-CLK   [------------]          |
                        |          |------------|GND       |            |          |
                        |          |            |          |            |          |
                        |          |            +----------+            |          |
                        |          |                                    |          |
                        |          [------------------------------------]          |
+----------+            |          [               USB                  ]          |
|          |---(MOSI)---|          [------------------------------------]          |
|          |---(MISO)---|          |                                    |          |
|          |---(SCLK)---|          |                                    |          |
|          |---(SS)-----|          |-------+                            |          |
|          |---(RESET)--|          |---+   |                            |          |
|          |            |          |   |   |                            |          |
|   PHY    |            |          |   | (GND)                          |          |
|          |            +----------+  (5V) |                            |          |
|          |                           |   |                            |          |
|          |            +----------+   |   |                            |          |
|          |---(3V3)----|5v->3.3V  |---+   |                            |          |
|          |---(GND)----|Regulator |-------+                            |          |
+----------+            +----------+                                    +----------+
```

- Supplied from USB-TTL(Without firmware flash)
```
                        +----------+            +----------+            +----------+
                        |BluePill  |            |USB-TTL   |            |HOST      |
                        |BlackPill |            |          [------------]          |
                        |          |----(5V)----|          [    USB     ]          |
                        |          |----(GND)---|          [------------]          |
                        |          |            |          |            |          |
                        |          |            |          |            |          |
                        |          |            |          |            |          |
                        |          |            |          |            |          |
                        |          |            |          |            |          |
+----------+            |       PA9|------------|RX        |            |          |
|          |---(MOSI)---|          |            |          |            |          |
|          |---(MISO)---|          |            |          |            |          |
|          |---(SCLK)---|          |            |          |            |          |
|          |---(SS)-----|          |-------+    |          |            |          |
|          |---(RESET)--|          |---+   |    |          |            |          |
|          |            |          |   |   |    |          |            |          |
|   PHY    |            |          |   | (GND)  |          |            |          |
|          |            +----------+  (5V) |    |          |            |          |
|          |                           |   |    |          |            |          |
|          |            +----------+   |   |    |          |            |          |
|          |---(3V3)----|5v->3.3V  |---+   |    |          |            |          |
|          |---(GND)----|Regulator |-------+    |          |            |          |
+----------+            +----------+            +----------+            +----------+
```

- Supplied from USB Port(Without firmware flash)
```
                        +----------+                                    +----------+
                        |BluePill  |                                    |HOST      |
                        |BlackPill [------------------------------------]          |
                        |          [                USB                 ]          |
                        |          [------------------------------------]          |
                        |          |                                    |          |
                        |          |                                    |          |
                        |          |                                    |          |
                        |          |                                    |          |
                        |          |                                    |          |
+----------+            |          |                                    |          |
|          |---(MOSI)---|          |                                    |          |
|          |---(MISO)---|          |                                    |          |
|          |---(SCLK)---|          |                                    |          |
|          |---(SS)-----|          |-------+                            |          |
|          |---(RESET)--|          |---+   |                            |          |
|          |            |          |   |   |                            |          |
|   PHY    |            |          |   | (GND)                          |          |
|          |            +----------+  (5V) |                            |          |
|          |                           |   |                            |          |
|          |            +----------+   |   |                            |          |
|          |---(3V3)----|5v->3.3V  |---+   |                            |          |
|          |---(GND)----|Regulator |-------+                            |          |
+----------+            +----------+                                    +----------+
```


# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/DhcpAddressPrinter
pio run -t upload -e bluepill_f103c8
```

# Using STM Virtual COM port   
Serial.print goto USB Virtual COM port.   
/dev/ttyACM0 may be change.   
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/DhcpAddressPrinter
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# Note
- I has not been tested on a real W5200 controller.   
- It cannot retrieve the Internal MAC address from WIZ550io.   


# More information
See [here](https://www.arduino.cc/en/Reference/Ethernet).

