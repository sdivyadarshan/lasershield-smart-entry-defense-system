# Algorithm

1. Initialize GPIO, serial communication, and servo; set servo to open and switch off alarm outputs.
2. Wait for the arm/disarm button.
3. While armed and no alarm is active, read the LDR comparator DO output.
4. Compare DO against the configured beam-interrupted logic level.
5. Require the interrupted state to remain stable for SENSOR_CONFIRM_MS.
6. On confirmation, latch the alarm and move the servo to the closed angle.
7. Toggle buzzer and LED at BLINK_INTERVAL_MS while the alarm is active.
8. On silence-button press during an alarm, stop buzzer/LED and move servo to the third position.
9. On disarm, clear the alarm and return servo to the open angle.

## State variables
- systemArmed — enables optical monitoring.
- alarmActive — latched alarm state.
- sensorCandidateBroken — candidate sensor condition.
- blinkState — current buzzer/LED phase.
- Button stable/last readings and timestamps — debounce logic.

## Parameters
Button debounce: 60 ms. Sensor confirmation: 35 ms. Alarm blink interval: 250 ms. Servo positions: open 0°, closed 120°, silence 30°. Tune these values only after physical testing and checking mechanical travel.
