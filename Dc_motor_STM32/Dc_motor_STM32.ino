const int pwmPin = PA8;
const int currentSensorPin = PA0;
const int buttonPin = PA1;
const int ledPin = PA2;
const float CURRENT_THRESHOLD = 2.0;  // Threshold in Amps
bool motorRunning = false;

void setup() {
  pinMode(pwmPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  analogWrite(pwmPin, 0);  // Start with motor off
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Button pressed
    delay(200);  // Debounce delay
    motorRunning = !motorRunning;
    if (motorRunning) {
      analogWrite(pwmPin, 128);  // 50% duty cycle
    } else {
      analogWrite(pwmPin, 0);  // Stop motor
    }
  }

  float current = readCurrent();
  if (current > CURRENT_THRESHOLD) {
    analogWrite(pwmPin, 0);  // Stop motor
    digitalWrite(ledPin, HIGH);  // Fault LED ON
  } else {
    digitalWrite(ledPin, LOW);  // Fault LED OFF
  }
}

float readCurrent() {
  int adcValue = analogRead(currentSensorPin);
  float voltage = adcValue * (3.3 / 1024.0);  // Calculate voltage from ADC value
    return (voltage - 2.5) / 0.066;  // Adjust 0.066 for ACS712-30A; change for 5A or 20A versions
}