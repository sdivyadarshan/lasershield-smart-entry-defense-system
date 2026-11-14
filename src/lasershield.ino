/*
  LaserShield – Smart Entry Defense System
  Board      : Raspberry Pi Pico (RP2040)
  IDE        : Arduino IDE (Earle Philhower core)
  Sensor     : LDR Module (Digital OUT, calibrated)
*/

#include <Servo.h>

// -------- PIN DEFINITIONS (GPIO numbers) --------
#define LDR_PIN        0   // GP0  - LDR module digital OUT
#define BTN_POWER      1   // GP1  - Power ON/OFF button (to GND)
#define BTN_SILENCE    2   // GP2  - Silence button (to GND)
#define SERVO_PIN      3   // GP3  - Servo signal
#define BUZZER_PIN    4   // GP4  - Buzzer (or transistor base)
#define LED_PIN       5   // GP5  - Red LED

// -------- SERVO POSITIONS --------
#define SERVO_OPEN_ANGLE     0
#define SERVO_CLOSED_ANGLE   120
#define SERVO_SILENCE_ANGLE  30   // Position-3

// -------- SYSTEM SETTINGS --------
#define IR_ACTIVE_HIGH_FOR_BREAK true   // LDR OUT = HIGH when beam broken
#define IR_CONFIRM_READS         3
#define DEBOUNCE_DELAY           60
#define BLINK_INTERVAL           250

Servo gateServo;

// -------- SYSTEM STATES --------
bool systemArmed = false;
bool alarmActive = false;

unsigned long lastPowerTime = 0;
unsigned long lastSilenceTime = 0;
unsigned long lastBlinkTime = 0;

bool blinkState = false;
int ldrCount = 0;

// -------- SETUP --------
void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(BTN_POWER, INPUT_PULLUP);
  pinMode(BTN_SILENCE, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(SERVO_OPEN_ANGLE);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println("LaserShield (Arduino) Ready");
}

// -------- LOOP --------
void loop() {
  unsigned long now = millis();

  // -------- POWER BUTTON (ARM / DISARM) --------
  if (digitalRead(BTN_POWER) == LOW) {
    if (now - lastPowerTime > DEBOUNCE_DELAY) {
      systemArmed = !systemArmed;
      lastPowerTime = now;

      if (systemArmed) {
        Serial.println("System ARMED");
        digitalWrite(LED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_PIN, LOW);
      } else {
        Serial.println("System DISARMED");
        alarmActive = false;
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        gateServo.write(SERVO_OPEN_ANGLE);
      }
    }
  }

  // -------- LDR BEAM CHECK --------
  if (systemArmed && !alarmActive) {
    int sensorVal = digitalRead(LDR_PIN);
    bool beamBroken = IR_ACTIVE_HIGH_FOR_BREAK ? (sensorVal == HIGH) : (sensorVal == LOW);

    if (beamBroken) {
      ldrCount++;
    } else {
      ldrCount = 0;
    }

    if (ldrCount >= IR_CONFIRM_READS) {
      Serial.println("Beam Interrupted! Alarm ON");
      alarmActive = true;
      gateServo.write(SERVO_CLOSED_ANGLE);
      lastBlinkTime = now;
      blinkState = false;
      ldrCount = 0;
    }
  }

  // -------- SILENCE BUTTON --------
  if (alarmActive && digitalRead(BTN_SILENCE) == LOW) {
    if (now - lastSilenceTime > DEBOUNCE_DELAY) {
      Serial.println("Alarm Silenced – Servo Position 3");
      alarmActive = false;
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
      gateServo.write(SERVO_SILENCE_ANGLE);
      lastSilenceTime = now;
    }
  }

  // -------- ALARM BLINKING --------
  if (alarmActive) {
    if (now - lastBlinkTime >= BLINK_INTERVAL) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      digitalWrite(BUZZER_PIN, blinkState);
      digitalWrite(LED_PIN, blinkState);
    }
  }
}
