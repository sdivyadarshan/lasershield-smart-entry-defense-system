# LaserShield — Smart Entry Defense System

A Raspberry Pi Pico RP2040 optical beam-interruption alarm prototype. A low-power laser is aimed at an LDR comparator module. When an object blocks the beam, the Pico activates a buzzer and warning LED, and moves the servo to a closed position. The design is intended for learning, demonstrations, and prototyping rather than as a certified security device.

**Platform:** Raspberry Pi Pico RP2040 · **IDE:** Arduino IDE · **Firmware:** C++  
**Project type:** Educational hardware prototype — not a certified security system.

## Features
- Laser + LDR digital comparator beam-break detection
- Push-button arm/disarm control
- Separate alarm silence control
- SG90 servo positions: open, alarm/closed, and silence/position 3
- Blinking red LED and active buzzer
- Debounced buttons and sensor confirmation interval
- Configurable sensor output polarity

## Components
Raspberry Pi Pico RP2040 (USB-C clone), LDR comparator module, low-power toy laser, SG90 servo, active buzzer, red LED, LED series resistor, two push buttons, breadboard, jumper wires, USB cable, and a regulated 5 V power supply.

## Pin mapping

| Function | Pico GPIO | Physical pin |
|---|---:|---:|
| LDR module DO | GP0 | 1 |
| Arm/disarm button | GP1 | 2 |
| Silence button | GP2 | 4 |
| Servo signal | GP3 | 5 |
| Buzzer control/driver | GP4 | 6 |
| Red LED | GP5 | 7 |

See [wiring and components](hardware/wiring-and-components.md) and [pinout CSV](hardware/pinout.csv).

## Arduino IDE setup
1. Install an Arduino-compatible Raspberry Pi Pico/RP2040 board package.
2. Select the matching Pico board and the correct USB port.
3. Install or select a Servo library compatible with the chosen RP2040 core.
4. Open [src/lasershield.ino](src/lasershield.ino), compile it, and upload the sketch.
5. Open the Serial Monitor at **115200 baud**.

## Operation
1. Power the circuit with the laser aligned to the LDR.
2. Press ARM to start monitoring.
3. With the beam received, the alarm remains inactive.
4. Blocking the beam for the confirmation interval triggers the alarm and moves the servo to its closed angle.
5. Press SILENCE to stop the buzzer and LED, then move the servo to position 3.
6. Press ARM again to disarm and return the servo to the open angle.

## Calibration
The firmware default is `BEAM_BROKEN_LEVEL = LOW`. LDR comparator polarity varies by module, so observe the DO output with the beam present and blocked, adjust the onboard potentiometer for a stable threshold, and verify the logic before regular use.

## Electrical safety
- Use only a low-power laser and never aim it at eyes or reflective surfaces.
- Power the SG90 from a regulated external 5 V supply; connect that supply's GND to Pico GND. Do not power the servo from a GPIO.
- Fit a current-limiting resistor in series with the LED. PWM dimming is not a substitute.
- Check buzzer voltage/current; use a transistor driver if required.
- Keep all Pico GPIO signals within 3.3 V logic levels.

## Repository guide
- [src/lasershield.ino](src/lasershield.ino) — Arduino sketch
- [hardware/wiring-and-components.md](hardware/wiring-and-components.md) — wiring details and component notes
- [hardware/pinout.csv](hardware/pinout.csv) — pin mapping table
- [PROJECT DOCUMENTATION.md](PROJECT%20DOCUMENTATION.md) — full project overview, setup, testing, troubleshooting, and design notes
- [media/README.md](media/README.md) — media and demo file placeholders
- [docs/](docs/) — architecture, design choices, validation, and future-scope notes

## Contribution and AI disclosure
The student developer selected the concept and components, assembled the hardware, aligned and calibrated the sensor, tested the servo, and defined the intended operating behavior. AI assistance was used to improve the structure, clarity, and documentation while preserving the original project intent and implementation decisions.

## License
The repository's MIT License is retained. Review its copyright attribution before redistribution.
