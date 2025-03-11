#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* SSID = "IT-Berufe";
const char* PSK = "79235686";
const char* MQTT_BROKER = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
int counter = 0;

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1883);
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
            client.connect("ESP8266Client");
            Serial.println("broker connected");

                char msg[20]; 
                sprintf(msg, "Luca: %d", counter); 

                client.publish("/test/counter-test", msg);
                Serial.println(msg);

                counter++;

            delay(2000);
        }
    }
    client.loop();

    delay(2000);
}
