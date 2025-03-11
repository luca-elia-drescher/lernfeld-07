#include <LiquidCrystal_I2C.h>

const double criticalTemp = 28.00;

const int green = 3;
const int yellow = 2;
const int red = 4;
const int beeper = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); 

  Serial.begin(9600);
  
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  pinMode(beeper, OUTPUT);
}

void loop() {
  double voltage = analogRead(0) * (4.85 / 1024.0); // voltage on board was measured at 4.85V instead of 5.0V
  double temp = (voltage - 0.5) * 100.0; 
  int debugValue = analogRead(0);

  lcd.setCursor(6, 0);
  lcd.print(temp, 1);
  lcd.print(" C ");

  if (temp >= criticalTemp) {
    digitalWrite(beeper, HIGH);
    delay(1000);
    digitalWrite(beeper, LOW);
    delay(1000);

    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  } else if (temp >= (criticalTemp - 5)) {
    digitalWrite(beeper, LOW);

    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
  } else {
    digitalWrite(beeper, LOW);

    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
  }

  Serial.println(voltage); 
  //Serial.println(temp); 

  delay(500);
}
