#include <SoftwareSerial.h>

SoftwareSerial softSerial(10, 11);

void setup() {
  softSerial.begin(38400);
  Serial.begin(9600);
  Serial.println("Device connected.it s");
  delay(500);
}

void loop() {
  if (softSerial.available())
    Serial.write(softSerial.read());
  if (Serial.available())
    softSerial.write(Serial.read());
}