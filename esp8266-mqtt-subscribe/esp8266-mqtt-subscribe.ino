#include <ESP8266WiFi.h>  // Library to handle WiFi connectivity on ESP8266
#include <PubSubClient.h> // Library to enable MQTT communication

// WiFi credentials
const char* SSID = "IT-Berufe";
const char* PSK = "79235686";

// MQTT broker details
const char* MQTT_BROKER = "broker.hivemq.com"; // Public MQTT broker address
int counter = 0; // Counter variable 

// Create WiFi and MQTT client objects
WiFiClient espClient;      
PubSubClient client(espClient); // Initialize MQTT client

void setup() {
  Serial.begin(115200); 
  setup_wifi();
  client.setServer(MQTT_BROKER, 1883); // Set the MQTT broker and port
  client.setCallback(callback); // Assign a function to handle received messages
}

void setup_wifi() {
  WiFi.begin(SSID, PSK); // Start connecting to the WiFi network
  while (WiFi.status() != WL_CONNECTED) { // Wait until connected
    delay(100);
  }
  Serial.println(WiFi.localIP()); // Print the device's assigned IP address
}

// Callback function executed when a message is received on a subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (byte i = 0; i < length; i++) { 
    char tmp = char(payload[i]); // Convert byte to character
    msg += tmp; // Append character to string
  }
  Serial.println(msg); // Print received message to Serial Monitor
}

void loop() {
  if (!client.connected()) {  // Check if the MQTT client is connected
    while (!client.connected()) { 
      client.connect("ESP8266ClientLuca"); // Attempt to connect to MQTT broker
      client.subscribe("/test/test/luca"); // Subscribe to the specified topic
      Serial.println("broker connected"); // Print connection status
      delay(100);
    }
  }
  client.loop();

  counter++; // Increment the counter variable

  char msg[20];  // Create a message with the counter value
  sprintf(msg, "Luca: %d", counter); // Format message as "Luca: <counter>"
  client.publish("/test/test/luca", msg); // Publish message to the MQTT topic

  delay(1000);
}
