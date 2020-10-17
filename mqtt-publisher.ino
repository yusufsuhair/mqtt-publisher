#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h> 
#include <PubSubClient.h> 
#include <BlynkSimpleEsp8266.h>

const char* ssid = "Samsung";
const char* wifi_password = "sarutof99";
const char* mqtt_server = "192.168.100.201";
const char* mqtt_topic = "testTopic";
char auth[] = "vC9H8wMmNsi71b2ckFEK3XLwgL2M3vsL";
const char* clientID = "Yusuf";
String pts = "0";

WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

BLYNK_WRITE (V3) {
  pts = param.asStr();
  Serial.println(pts);
  
}

void setup() {

  Serial.begin(9600);

  Blynk.begin(auth, ssid, wifi_password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}

void loop() {

  Blynk.run();

  if (pts != "0") {
    client.publish(mqtt_topic, (char*) pts.c_str());
    Serial.println("Published");
    pts = "0";
  } else {
    Serial.println("Waiting for Publish"); 
  }

  delay(3000);
}
