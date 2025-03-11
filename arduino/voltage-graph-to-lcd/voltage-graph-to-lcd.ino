#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// max = 5V = 1023; min = 0V = 0
// to determine the step size we calculate max divided by 5
// step = 5V/5 = 1V; step= 1023/5 = 204,6

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(5);
  double voltage = value / 204.6;
  lcd.setCursor(0, 0);

  Serial.println(value);
  Serial.println(voltage);

  lcd.print(voltage);

  delay(200);
}
