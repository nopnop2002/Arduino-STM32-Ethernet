# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/DhcpAddressPrinter
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
Serial.print goto USB Virtual COM port.   
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/DhcpAddressPrinter
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# Screen Shot
![Screen_DhcpAddressPrinter](https://user-images.githubusercontent.com/6020549/169679491-367d3085-e57c-4595-af20-3ade5524b261.jpg)
