char data;
char ledStatus;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
  }

  if (data == '1') {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
}