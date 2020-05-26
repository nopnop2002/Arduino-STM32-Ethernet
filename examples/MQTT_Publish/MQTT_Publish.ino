/*
 * W5500 Ethernet Module MQTT Publish.
 */

#include <SPI.h>
#include <Ethernet_STM.h>
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient

#define INTERVAL        30 // Publish Interval
//#define MQTT_SERVER     "broker.hivemq.com"
//#define MQTT_SERVER     "iot.eclipse.org"
#define MQTT_SERVER     "192.168.10.40"
#define MQTT_PORT       1883
#define MQTT_TOPIC      "arduino/STM"
#define MQTT_WILL_TOPIC "arduino/STM"
#define MQTT_WILL_MSG   "I am leaving..." // You can change

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

#if defined(W5100_ETHERNET_SHIELD)
  #define MODULE         "W5100"
#elif defined(W5200_ETHERNET_SHIELD)
  #define MODULE         "W5200"
#elif defined(W5500_ETHERNET_SHIELD)
  #define MODULE         "W5500"
#endif

EthernetClient ethClient;
PubSubClient pubsubClient(ethClient);

unsigned long lastMillis;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void errorDisplay(char* buff) {
  Serial.print("Error:");
  Serial.println(buff);
  while(1) {
    delay(100);
  }
}

void setup() {
  delay(1000);Serial.begin(115200);
  Serial.print("Ethernet begin....");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("faild");
    while(1) {}
  }
  Serial.println("ok");
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());
  
  pubsubClient.setServer(MQTT_SERVER, MQTT_PORT);
  pubsubClient.setCallback(callback);

  char clientid[30];
  IPAddress ip = Ethernet.localIP();
  sprintf(clientid,"%03d-%03d-%03d-%03d",ip[0], ip[1], ip[2], ip[3]);
  Serial.print("clientid=");
  Serial.println(clientid);
  // Loop until we're reconnected
  while (!pubsubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // connect (String id, String willTopic, uint8_t willQos, bool willRetain, String willMessage)
    if (pubsubClient.connect(clientid,MQTT_WILL_TOPIC,0,0,MQTT_WILL_MSG)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(pubsubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  lastMillis = 0;
}

void loop() {
  static int counter = INTERVAL;
  static int value = 0;
  char payload[50];

  pubsubClient.loop();
  unsigned long now = millis();
  if (now - lastMillis > 1000) { // 1秒経過
    lastMillis = now;
    counter++;
    if (counter > INTERVAL) {
      ++value;
      snprintf (payload, 75, "MQTT from Arduino/UNO %06d",value);
#ifdef ARDUINO_ARCH_STM32
      snprintf (payload, 75, "MQTT from Arduino/STM32 %06d",value);
#endif
      Serial.print("["+String(MODULE)+"] Publish message: ");
      Serial.println(payload);
      if (!pubsubClient.publish(MQTT_TOPIC, payload) ) {
         errorDisplay("Failed to Publsh");
      }
      counter=0;
    }
  }
}
