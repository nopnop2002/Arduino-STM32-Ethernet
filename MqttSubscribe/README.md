# Build
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd MqttSubscribe
pio run -t upload -e bluepill_f103c8 && pio device monitor -b 115200 -p /dev/ttyUSB0
```

# MQTT Publish using python
```
chmod 777 mqtt_pub.sh
./mqtt_pub.sh
```
