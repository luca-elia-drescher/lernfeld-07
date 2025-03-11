int red = 2;
int yellow = 3;
int green = 4; 
int button = 8;
int buttonState = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(green, HIGH);
  buttonState = digitalRead(button);

  if (buttonState == HIGH) {
    delay(3000);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    delay(1000);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    delay(5000);
    digitalWrite(yellow, HIGH);
    delay(1000);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  }
}
