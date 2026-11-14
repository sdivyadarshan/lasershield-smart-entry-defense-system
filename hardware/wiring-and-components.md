# Wiring and Components

| Device | Connection | Pico |
|---|---|---|
| LDR module | DO | GP0 |
| LDR module | VCC | 3V3 OUT (verify module supports 3.3 V) |
| LDR module | GND | GND |
| Arm button | One side | GP1; other side to GND |
| Silence button | One side | GP2; other side to GND |
| SG90 | Signal | GP3 |
| SG90 | Red V+ | External regulated 5 V |
| SG90 | Brown/black GND | External GND, joined to Pico GND |
| Buzzer | Control | GP4; use transistor driver if load requires |
| Red LED | Anode | GP5 through a current-limiting resistor; cathode to GND |

## Components
- Raspberry Pi Pico RP2040 USB-C clone — 1
- LDR digital comparator module — 1
- Low-power toy laser — 1
- SG90 servo — 1
- Active buzzer — 1
- Red LED and series resistor — 1 each
- Push buttons — 2
- Breadboard, jumper wires, USB cable
- Regulated external 5 V supply for servo

## Laser alignment and calibration
Aim the low-power laser at the LDR sensing surface. Adjust the module potentiometer until its DO output changes reliably between beam-present and beam-blocked conditions. Observe the logic level in the Serial Monitor and configure BEAM_BROKEN_LEVEL accordingly. Shield the LDR from changing ambient light where possible.

## Power precautions
Power the servo from a separate regulated 5 V supply with adequate current capacity. Join the supply ground to Pico GND. Never apply 5 V to a Pico GPIO. A discrete LED requires a series resistor; PWM dimming cannot replace it. Check the buzzer's electrical rating and add a transistor driver if its current exceeds safe GPIO drive capability. Disconnect power before rewiring.
