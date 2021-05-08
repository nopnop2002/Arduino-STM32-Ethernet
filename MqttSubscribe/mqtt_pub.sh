#!/bin/bash
#set -x
count=1
while :
do
        #payload=$(date +"%T")
        payload="text${count}"
        echo ${payload}
        mosquitto_pub -h broker.hivemq.com -p 1883 -t "/arduino/STM32" -m ${payload}
        count=$((++count))
        sleep 10
done
