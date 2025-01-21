#include <ESP8266WiFi.h>

const char* ssid  = "obi-wlan kenobi";
const char* password = "passwort123";

WiFiServer server(80);
String header;
String ledState = "off";

const int led = 2;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  Serial.println("Starte AccessPoint...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client verbunden");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /D1/on") >= 0) {
              Serial.println("GPIO on");
              ledState = "on";
              digitalWrite(led, HIGH);
            } else if (header.indexOf("GET /D1/off") >= 0) {
              Serial.println("GPIO off");
              ledState = "off";
              digitalWrite(led, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            client.println("<body><h1>ESP8266 Web Server</h1>");
            client.println("<p>GPIO - Status ");
            if (ledState == "off") {
              client.println("<p><a href=\"/D1/on\"><button class=\"button button2\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/D1/off\"><button class=\"button\">ON</button></a></p>");
            }
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client getrennt.");
    Serial.println("");
  }
}