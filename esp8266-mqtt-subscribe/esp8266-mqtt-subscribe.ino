#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "IT-Berufe";
const char* PSK = "79235686";
const char* MQTT_BROKER = "broker.hivemqt.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(500);
  setup_wifi();
  client.setServer(MQTT_BROKER, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println(WiFi.localIP());
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      client.connect("ESP8266Luca");
      client.subscribe("michael/CPS");
      delay(100);
    }
  }
  client.loop();
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (byte i = 0; i < length; i++) {
    char tmp = char(payload[i]);
    msg += tmp;
  }
  Serial.println(msg);
}