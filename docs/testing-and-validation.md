# Testing and Validation

This is a test plan. Mark a test as passed only after performing it on the assembled hardware and recording the actual observation.

## Pre-power checklist
- [ ] Confirm Pico GPIO and physical pin mapping.
- [ ] Confirm LDR module supply and DO output are 3.3 V safe.
- [ ] Confirm buttons connect GP1/GP2 to GND.
- [ ] Confirm LED series resistor is installed.
- [ ] Confirm servo uses external regulated 5 V and common ground.
- [ ] Confirm buzzer rating and driver circuit.
- [ ] Align low-power laser safely, away from eyes.

## Functional test matrix

| ID | Test | Expected result | Result |
|---|---|---|---|
| T01 | Power up | Outputs off; servo at open angle | Not recorded |
| T02 | Press ARM | Serial Monitor reports SYSTEM ARMED | Not recorded |
| T03 | Beam reaches LDR | No alarm | Not recorded |
| T04 | Block beam while armed | Alarm triggers after confirmation | Not recorded |
| T05 | Alarm active | Buzzer/LED blink; servo closes | Not recorded |
| T06 | Press SILENCE | Alarm stops; servo moves to position 3 | Not recorded |
| T07 | Press ARM to disarm | Alarm clears; servo returns open | Not recorded |
| T08 | Hold a button | No repeated press events | Not recorded |
| T09 | Repeat interruption | Behavior remains consistent | Not recorded |
| T10 | Servo movement under load | Pico remains stable | Not recorded |

## Calibration procedure
1. Open Serial Monitor at 115200 baud.
2. Observe LDR DO with the beam present and blocked.
3. Adjust the comparator potentiometer until the states are distinct and stable.
4. Set BEAM_BROKEN_LEVEL to the measured interrupted-beam logic level.
5. Repeat under expected room-light conditions.

Record date, lighting, sensor polarity, supply details, and observed behavior. Do not treat a servo-only test as proof that the complete alarm system passed.

## Known limitations
LDR response depends on ambient light and alignment. The prototype does not independently distinguish laser failure from beam interruption and is not a certified security device.
