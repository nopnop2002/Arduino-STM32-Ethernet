# Build
```
git clone https://github.com/nopnop2002/Arduino-STM32-Ethernet
cd Arduino-STM32-Ethernet
cd MqttPublish
pio run -t upload -e bluepill_f103c8 && pio device monitor -b 115200 -p /dev/ttyUSB0
```

# MQTT Subscribe using python
```
chmod 777 mqtt_sub.sh
./mqtt_sub.sh
```
