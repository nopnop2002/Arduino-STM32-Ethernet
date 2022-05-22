# Environment
```
 '-D MQTT_SERVER="broker.hivemq.com"'
```

# Using USB-TTL converter   
Serial.print goto PA9.
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/MqttSubscribe
pio run -e bluepill_f103c8 -t upload
```

# Using STM Virtual COM port   
Serial.print goto USB Virtual COM port.   
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet/MqttSubscribe
pio run -e bluepill_f103c8_usbcon -t upload && pio device monitor -b 115200 -p /dev/ttyACM0
```

# MQTT Publish using python
```
sudo apt install mosquitto-clients moreutils
chmod 777 mqtt_pub.sh
./mqtt_pub.sh
```

# Screen Shot
![Screen_MqttSubscribe](https://user-images.githubusercontent.com/6020549/169679099-aa6ff0dc-bfe4-4079-88c4-c5d03df507d3.jpg)

