int blue = 7;
int red = 8;
int buttonPin = 5;

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {  
    digitalWrite(blue, HIGH);
    digitalWrite(red, LOW);
    delay(250);

    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
    delay(250);

  } else {
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }
}
