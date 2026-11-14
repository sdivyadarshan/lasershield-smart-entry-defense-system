# System Architecture

Laser source → optical beam → LDR comparator module → Raspberry Pi Pico RP2040.

**Inputs:** LDR module digital output, arm/disarm button, silence button.  
**Controller:** Pico reads and filters input changes, handles operating states, and drives outputs.  
**Outputs:** SG90 servo, active buzzer, red LED.

The laser provides a continuous beam aimed at the LDR. The LDR comparator converts light level into a digital output. The Pico interprets a calibrated output transition as beam interruption. The buzzer and LED indicate an alarm; the servo demonstrates a gate/door actuator with open, closed, and silence positions.

The Pico logic uses 3.3 V GPIO. The servo is powered from an external regulated 5 V supply; its ground must be common with Pico GND. The LDR comparator module supply and output voltage must be verified as 3.3 V compatible.
