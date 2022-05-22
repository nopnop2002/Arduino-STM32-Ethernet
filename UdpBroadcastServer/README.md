# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/UdpBroadcastServer
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
Serial.print goto USB Virtual COM port.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/UdpBroadcastServer
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# Screen Shot
![Screen_UdpBroadcastServer](https://user-images.githubusercontent.com/6020549/169679090-74b7a624-37f4-4620-b3cd-cb2da6db2b39.jpg)

# UDP Broadcast Client
```
python3 udp-transfer.py
```
