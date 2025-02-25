#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "IT-Berufe";
const char* PSK = "79235686";
const char* MQTT_BROKER = "broker.hivemq.com";
int counter = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
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

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (byte i = 0; i < length; i++) {
    char tmp = char(payload[i]);
    msg += tmp;
  }
  Serial.println(msg);
}

void loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      client.connect("ESP8266ClientLuca");
      client.subscribe("/test/test/luca");
      Serial.println("broker connected");
      delay(100);
    }
  }
  client.loop();

  counter++;

  char msg[20];
  sprintf(msg, "Luca: %d", counter);
  client.publish("/test/test/luca", msg);

  delay(1000);
}