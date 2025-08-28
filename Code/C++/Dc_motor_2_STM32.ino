#include <Arduino.h>

// === Pin Definitions ===
#define PWM_PIN            PA8
#define CURRENT_SENSOR_PIN PA0
#define BUTTON_PIN         PA1
#define LED_PIN            PA2

// === Constants ===
#define CURRENT_THRESHOLD  2.0      // Current threshold in Amps
#define PWM_MAX            255      // 8-bit resolution
#define PWM_DUTY_50        (PWM_MAX / 2)
#define DEBOUNCE_DELAY     200      // ms debounce delay

// === Variables ===
bool motorRunning = false;
unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;

// === Setup Function ===
void setup() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  analogWrite(PWM_PIN, 0);  // Ensure motor is off at start
  Serial.begin(9600);
  Serial.println("System Initialized...");
}

// === Main Loop ===
void loop() {
  // --- Button handling with debounce ---
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime > DEBOUNCE_DELAY)) {
    motorRunning = !motorRunning;   // Toggle motor state
    lastDebounceTime = millis();    // Reset debounce timer

    if (motorRunning) {
      analogWrite(PWM_PIN, PWM_DUTY_50);  // Run motor at 50% duty cycle
      Serial.println("Motor Started at 50% duty");
    } else {
      analogWrite(PWM_PIN, 0);  // Stop motor
      Serial.println("Motor Stopped");
    }
  }
  lastButtonState = buttonState;

  // --- Current Monitoring ---
  float current = readCurrent();
  Serial.print("Current (A): ");
  Serial.println(current, 3); // print with 3 decimal places

  if (current > CURRENT_THRESHOLD) {
    analogWrite(PWM_PIN, 0);       // Stop motor immediately
    digitalWrite(LED_PIN, HIGH);   // Fault LED ON
    motorRunning = false;
    Serial.println("FAULT: Overcurrent detected! Motor stopped.");
  } else {
    digitalWrite(LED_PIN, LOW);    // Fault LED OFF
  }
}

// === Function to read current from ACS712 ===
float readCurrent() {
  int adcValue = analogRead(CURRENT_SENSOR_PIN);
  float voltage = adcValue * (3.3f / 1024.0f);  // STM32 ADC is 10-bit (0–1023) with 3.3V reference
  return (voltage - 2.5f) / 0.066f;             // ACS712-30A sensitivity: 66mV/A
}
