/*
 * W5500 Ethernet Module MQTT Publish example.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define INTERVAL        10 // Publish Interval [Seconds]
#define MQTT_SERVER     "broker.hivemq.com"
//#define MQTT_SERVER     "iot.eclipse.org"
#define MQTT_PORT       1883
#define MQTT_TOPIC      "/arduino/STM32"
#define MQTT_WILL_TOPIC "/arduino/STM32"
#define MQTT_WILL_MSG   "I am leaving..." // You can change

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

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
  // Open serial communications and wait for port to open:
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // You can use Ethernet.init(pin) to configure the CS pin
#if defined GPIO_CS
  Serial.print("GPIO_CS=");
  Serial.println(GPIO_CS);
  Ethernet.init(GPIO_CS);
#else
  Ethernet.init(PA4);
#endif


  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100) {
    Serial.println("W5100 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5200) {
    Serial.println("W5200 Ethernet controller detected.");
  }
  else if (Ethernet.hardwareStatus() == EthernetW5500) {
    Serial.println("W5500 Ethernet controller detected.");
  }
  
  // print your local IP address:
  Serial.print("Ethernet.localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("Ethernet.subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Ethernet.gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("Ethernet.dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());

  char clientid[30];
  IPAddress ip = Ethernet.localIP();
  sprintf(clientid,"%03d-%03d-%03d-%03d",ip[0], ip[1], ip[2], ip[3]);
  //strcpy(clientid, "CLIENT001");
  Serial.print("clientid=");
  Serial.println(clientid);
  pubsubClient.setServer(MQTT_SERVER, MQTT_PORT);
  pubsubClient.setCallback(callback);

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
  if (now - lastMillis > 1000) { // 1 Second
    lastMillis = now;
    counter++;
    if (counter > INTERVAL) {
      ++value;
      snprintf (payload, 75, "MQTT from STM32 %06d",value);
      Serial.print("Publish message: ");
      Serial.println(payload);
      if (!pubsubClient.publish(MQTT_TOPIC, payload) ) {
         errorDisplay("Failed to Publsh");
      }
      counter=0;
    }
  }
}

