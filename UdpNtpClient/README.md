# Environment
```
 '-D NTP_SERVER="pool.ntp.org"'
 -D TIME_ZONE=9
```

# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd UdpNtpClient
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
Serial.print goto USB Virtual COM port.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd UdpNtpClient
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# Screen Shot
![Screen_UdpNtpClient](https://user-images.githubusercontent.com/6020549/169679093-d0ebab57-90e5-4dbb-8bd0-1006d04a4fee.jpg)

