#!/bin/bash
# sudo apt install mosquitto-clients
# sudo apt install moreutils
mosquitto_sub -d -h broker.hivemq.com -p 1883  -t "/arduino/#" | ts "%y/%m/%d %H:%M:%S"
#mosquitto_sub -d -h iot.eclipse.org -p 1883  -t "/arduino/#" | ts "%y/%m/%d %H:%M:%S"
