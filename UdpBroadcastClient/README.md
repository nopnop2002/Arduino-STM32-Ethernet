# Build
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd UdpBroadcastClient
pio run -t upload -e bluepill_f103c8 && pio device monitor -b 115200 -p /dev/ttyUSB0
```

# UDP Broadcast Receiver
```
python udp-receive.py
```


