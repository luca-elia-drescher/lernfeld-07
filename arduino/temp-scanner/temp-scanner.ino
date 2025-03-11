// V = (10mV/°C × t) + 500mV
// Rearranged for temp (t): t = (V - 0.5V) / (10mV/°C)

void setup() {
  Serial.begin(9600);
}

void loop() {
  double voltage = analogRead(0) * (5.0 / 1024.0);  
  double temp = (voltage - 0.5) * 100.0; // temp (°C) = (voltage - 0.5) * 100

  Serial.println(temp); 
  delay(100);
}
