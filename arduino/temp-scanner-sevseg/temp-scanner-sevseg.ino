#include "SevSeg.h"
SevSeg sevseg;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 100;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = { 2, 3, 4, 5 };
  byte segmentPins[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentMillis;

    double voltage = analogRead(0) * (5.0 / 1024.0);
    double temp = (voltage - 0.5) * 100.0;

    int displayTemp = static_cast<int>(temp * 100);  // scale by 100 for 2 decimal places
    sevseg.setNumber(displayTemp, 2);
  }

  sevseg.refreshDisplay();
}
