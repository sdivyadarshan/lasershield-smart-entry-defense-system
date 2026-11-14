# Design Decisions

- **Controller:** Raspberry Pi Pico RP2040 provides GPIO and PWM capability for the prototype.
- **Optical detection:** A laser is aimed at an LDR comparator module. The intended normal state is beam received; an interruption changes the module's DO logic level.
- **Calibration:** DO polarity differs between modules and comparator settings, so BEAM_BROKEN_LEVEL is configurable and must be confirmed experimentally.
- **Controls:** Two independent buttons separate arm/disarm from alarm silence. INPUT_PULLUP wiring connects each button between GPIO and GND.
- **Actuation:** Servo positions are 0° open, 120° closed, and 30° after silence. These are initial values and must be checked against the mechanical linkage.
- **Power:** External regulated 5 V powers the SG90 to avoid loading the Pico supply; grounds are common.
- **Protection:** A discrete LED needs a series resistor. A transistor driver may be needed for the buzzer.
- **Development:** Arduino IDE C++ is the repository firmware. MicroPython was used during early setup and testing.
