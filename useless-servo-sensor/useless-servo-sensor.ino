#include "Servo.h"

Servo Servomotor;
int Sensor = 8;
int SensorStatus = 0;

void setup() {
  Servomotor.attach(7);
  pinMode(Sensor, INPUT);
}

void loop() {
  SensorStatus = digitalRead(Sensor);

  if (SensorStatus == HIGH) {
    Servomotor.write(0);
    delay(1000);

    Servomotor.write(90);
    delay(1000);

    Servomotor.write(180);
    delay(1000);

    Servomotor.write(20);
    delay(1000);
  }
}
