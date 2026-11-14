/*
  LaserShield — Smart Entry Defense System
  Raspberry Pi Pico RP2040 | Arduino IDE
  LDR comparator DO: default LOW = beam interrupted.
  Confirm polarity on your module and change BEAM_BROKEN_LEVEL if needed.

  Wiring safety: SG90 on external regulated 5V with common GND;
  LED must have a series resistor; use a driver for buzzer loads as needed.
*/
#include <Arduino.h>
#include <Servo.h>

const uint8_t LDR_DO_PIN = 0;       // GP0
const uint8_t ARM_BUTTON_PIN = 1;  // GP1, button to GND
const uint8_t SILENCE_PIN = 2;     // GP2, button to GND
const uint8_t SERVO_PIN = 3;       // GP3
const uint8_t BUZZER_PIN = 4;      // GP4 / driver input
const uint8_t LED_PIN = 5;         // GP5 through series resistor

const uint8_t BEAM_BROKEN_LEVEL = LOW; // Change to HIGH if calibration requires it
const int SERVO_OPEN_ANGLE = 0;
const int SERVO_CLOSED_ANGLE = 120;
const int SERVO_SILENCE_ANGLE = 30;

const unsigned long DEBOUNCE_MS = 60;
const unsigned long BLINK_INTERVAL_MS = 250;
const unsigned long SENSOR_CONFIRM_MS = 35;

Servo gateServo;
bool systemArmed = false;
bool alarmActive = false;
bool blinkState = false;
bool armLast = HIGH, armStable = HIGH;
bool silenceLast = HIGH, silenceStable = HIGH;
unsigned long armChangedAt = 0, silenceChangedAt = 0;
unsigned long lastBlink = 0, sensorChangedAt = 0;
bool sensorCandidateBroken = false;

bool pressedEvent(uint8_t pin, bool &lastReading, bool &stableState,
                  unsigned long &changedAt, unsigned long now) {
  bool reading = digitalRead(pin);
  if (reading != lastReading) {
    lastReading = reading;
    changedAt = now;
  }
  if (now - changedAt >= DEBOUNCE_MS && reading != stableState) {
    stableState = reading;
    return stableState == LOW;
  }
  return false;
}

void setServoPosition(int angle) {
  gateServo.write(constrain(angle, 0, 180));
}

void stopAlarmOutputs() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  blinkState = false;
}

void triggerAlarm() {
  alarmActive = true;
  blinkState = false;
  lastBlink = millis();
  setServoPosition(SERVO_CLOSED_ANGLE);
  Serial.println(F("Beam interrupted: alarm active; servo closed"));
}

void updateAlarm(unsigned long now) {
  if (!alarmActive) {
    stopAlarmOutputs();
    return;
  }
  if (now - lastBlink >= BLINK_INTERVAL_MS) {
    lastBlink = now;
    blinkState = !blinkState;
    digitalWrite(BUZZER_PIN, blinkState ? HIGH : LOW);
    digitalWrite(LED_PIN, blinkState ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LDR_DO_PIN, INPUT);
  pinMode(ARM_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SILENCE_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  stopAlarmOutputs();

  gateServo.attach(SERVO_PIN);
  setServoPosition(SERVO_OPEN_ANGLE);

  armLast = armStable = digitalRead(ARM_BUTTON_PIN);
  silenceLast = silenceStable = digitalRead(SILENCE_PIN);
  Serial.println(F("LaserShield (Arduino / RP2040) ready"));
  Serial.println(F("Press ARM to begin monitoring."));
}

void loop() {
  const unsigned long now = millis();

  if (pressedEvent(ARM_BUTTON_PIN, armLast, armStable, armChangedAt, now)) {
    systemArmed = !systemArmed;
    if (systemArmed) {
      Serial.println(F("SYSTEM ARMED"));
      sensorCandidateBroken = false;
    } else {
      Serial.println(F("SYSTEM DISARMED"));
      alarmActive = false;
      stopAlarmOutputs();
      sensorCandidateBroken = false;
      setServoPosition(SERVO_OPEN_ANGLE);
    }
  }

  if (systemArmed && !alarmActive) {
    bool beamBroken = (digitalRead(LDR_DO_PIN) == BEAM_BROKEN_LEVEL);
    if (beamBroken != sensorCandidateBroken) {
      sensorCandidateBroken = beamBroken;
      sensorChangedAt = now;
    }
    if (sensorCandidateBroken && now - sensorChangedAt >= SENSOR_CONFIRM_MS) {
      triggerAlarm();
    }
  } else {
    sensorCandidateBroken = false;
  }

  if (pressedEvent(SILENCE_PIN, silenceLast, silenceStable, silenceChangedAt, now)
      && alarmActive) {
    alarmActive = false;
    stopAlarmOutputs();
    setServoPosition(SERVO_SILENCE_ANGLE);
    Serial.println(F("ALARM SILENCED: servo moved to position 3"));
  }

  updateAlarm(now);
  delay(5);
}
