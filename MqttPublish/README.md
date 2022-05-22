# Environment
```
 '-D MQTT_SERVER="broker.hivemq.com"'
 '-D MQTT_PAYLOAD="mqtt from stm32"'
```

# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/MqttPublish
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
Serial.print goto USB CIM port.   
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/MqttPublish
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# MQTT Subscribe using python
```
sudo apt install mosquitto-clients moreutils
chmod 777 mqtt_sub.sh
./mqtt_sub.sh
```

# Screen Shot
![Screen_MqttPublish](https://user-images.githubusercontent.com/6020549/169679097-bfc5aed9-12e7-4507-a2fa-7a0577efec99.jpg)

