// Initialize pin positions for RGB LED
int red = 3;
int green = 6;
int blue = 5;

/*
  max = 5V = 1023; min = 0V = 0
  to determine the step size we calculate max divided by 5
  step = 5V/5 = 1V; step= 1023/5 = 204,6
*/

// Setup function for pin modes and serial communication
void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  
  pinMode(8, INPUT_PULLUP); // Set pin 8 as input with pull-up resistor
  Serial.begin(9600); // Begin serial communication
}

void loop() {
  // Turn off all colors initially
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);

  if (digitalRead(8) == 0) { // Check if button (pin 8) is pressed
    int value = analogRead(5); // Read analog value from pin A5
    double voltage = value / 204.6; // Convert analog value to voltage
    Serial.println(voltage); // Print voltage value
    delay(10); // Small delay to avoid rapid polling

    // Set LED color based on voltage range
    if (voltage > 1 && voltage < 2) {
        analogWrite(blue, 255);
        Serial.println("blue");
    } else if (voltage >= 2 && voltage < 4) {
        analogWrite(green, 255);
        Serial.println("green");
    } else if (voltage >= 4) {
        analogWrite(red, 255);
        Serial.println("red");
    } else {
        // Turn off all LEDs if voltage doesn't match any range
        analogWrite(red, 0);
        analogWrite(green, 0);
        analogWrite(blue, 0);
    }
  }
}