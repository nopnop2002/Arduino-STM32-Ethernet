# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/UdpBroadcastClient
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/UdpBroadcastClient
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```


# UDP Broadcast Receiver
```
python3 udp-receive.py
```


