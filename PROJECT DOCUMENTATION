**PROJECT DOCUMENTATION**
=========================

**LaserShield – Smart Entry Defense System Using Raspberry Pi Pico (RP2040)**
-----------------------------------------------------------------------------

**1\. Project Overview**
------------------------

The **LaserShield Smart Entry Defense System** is a smart security prototype developed using the **Raspberry Pi Pico (RP2040)** and programmed using the **Arduino IDE**.The system uses a **laser break-beam principle** with an **LDR module** to detect unauthorized entry or object movement.

When the laser beam is interrupted, the system immediately responds by:

*   Activating a **servo motor** to close a gate or door
    
*   Triggering a **buzzer alarm**
    
*   Blinking a **warning LED**
    

Two push buttons are provided:

*   **Power Button** – to arm or disarm the system
    
*   **Silence Button** – to stop the alarm and move the servo to a third safety position
    

This project is suitable for **home security**, **locker protection**, **restricted area monitoring**, and **educational demonstrations**.

**2\. Development Platform**
----------------------------

*   **Microcontroller:** Raspberry Pi Pico (RP2040)
    
*   **Programming Language:** C/C++
    
*   **IDE Used:** **Arduino IDE**
    
*   **Board Support Package:** Arduino-Pico core (Earle Philhower)
    

The Arduino IDE was chosen because it provides:

*   Easy code uploading
    
*   Familiar syntax
    
*   Good library support
    
*   Reliable serial debugging
    

**3\. Working Principle**
-------------------------

A laser beam is continuously aimed at an **LDR sensor module**.

*   When the laser beam is **present**, the LDR module outputs a stable digital signal and the system remains idle.
    
*   When the laser beam is **blocked by an obstacle**, the sensor output changes state.
    
*   The Raspberry Pi Pico detects this change and immediately:
    
    1.  Closes the servo motor
        
    2.  Activates the buzzer alarm
        
    3.  Blinks the warning LED
        

Pressing the **Silence Button** stops the alarm and moves the servo to a predefined **Position 3**.Pressing the **Power Button** again disarms the system and resets it.

**4\. Hardware Components Used**
--------------------------------

### **Microcontroller**

*   Raspberry Pi Pico RP2040 (USB Type-C)
    

### **Input Devices**

*   LDR Sensor Module (Digital Output with comparator)
    
*   Laser Light
    
*   Push Button – Power ON/OFF
    
*   Push Button – Alarm Silence
    

### **Output Devices**

*   SG90 Servo Motor
    
*   Active Buzzer
    
*   Red LED
    

### **Power & Accessories**

*   External 5V power supply (servo + buzzer)
    
*   Breadboard
    
*   Jumper wires
    
*   USB Type-C cable
    

**5\. Pin Configuration (Raspberry Pi Pico)**
---------------------------------------------

ComponentGPIO PinLDR Module OUTGP0Power ButtonGP1Silence ButtonGP2Servo SignalGP3BuzzerGP4LEDGP5LDR VCC3.3VServo & Buzzer VCCExternal 5VAll GroundsCommon GND

⚠️ **All grounds must be connected together for proper operation.**

**6\. Software Implementation (Arduino IDE)**
---------------------------------------------

The program logic is written and uploaded using the **Arduino IDE**.The code performs the following operations:

*   Reads the digital output from the LDR module
    
*   Detects beam interruption
    
*   Controls servo position using PWM
    
*   Activates buzzer and LED during alarm state
    
*   Handles button input with software debounce
    
*   Implements multiple servo positions:
    
    *   **Open position**
        
    *   **Closed position**
        
    *   **Silence position**
        

The Arduino code continuously runs inside the loop() function and responds in real time to sensor and button inputs.

_(Arduino code already verified and uploaded successfully using Arduino IDE.)_

**7\. LDR Module Calibration**
------------------------------

1.  Aim the laser directly at the LDR module.
    
2.  Adjust the blue potentiometer on the LDR module.
    
3.  Ensure the OUT pin changes state only when the beam is blocked.
    
4.  Fine-tune for stable detection under ambient light.
    

This calibration allows the existing code logic to work without modification.

**8\. Testing Procedure**
-------------------------

1.  Power the Pico using USB and external 5V supply.
    
2.  Press the **Power Button** to arm the system.
    
3.  Ensure laser beam is aligned with the LDR.
    
4.  Block the laser beam:
    
    *   Servo closes
        
    *   Buzzer sounds
        
    *   LED blinks
        
5.  Press the **Silence Button**:
    
    *   Alarm stops
        
    *   Servo moves to Position 3
        
6.  Press **Power Button** again to disarm the system.
    

**9\. Troubleshooting**
-----------------------

**Laser not detected**

*   Misaligned laser
    
*   Improper LDR calibration
    
*   Loose wiring
    

**Servo not working**

*   Servo not powered with external 5V
    
*   Common ground missing
    

**Buzzer not sounding**

*   5V buzzer without transistor
    
*   Incorrect GPIO connection
    

**LED too dim**

*   Add resistor
    
*   Increase duty cycle in code
    

**10\. Future Scope**
---------------------

The LaserShield system can be enhanced further with the following upgrades:

1.  **Wireless Alerts**
    
    *   Add Wi-Fi or Bluetooth module to send alerts to mobile phones.
        
2.  **Camera Integration**
    
    *   Attach a camera module to capture intruder images.
        
3.  **Password or RFID Access**
    
    *   Allow authorized entry using keypad or RFID authentication.
        
4.  **Mobile App Control**
    
    *   Control arm/disarm and monitor status through a mobile app.
        
5.  **Data Logging**
    
    *   Store intrusion timestamps using RTC and SD card.
        
6.  **IoT Cloud Integration**
    
    *   Upload intrusion data to cloud dashboards for monitoring.
        
7.  **Battery Backup**
    
    *   Add rechargeable battery support for power failures.
        

**11\. Conclusion**
-------------------

The **LaserShield Smart Entry Defense System** demonstrates an effective integration of sensors, actuators, and microcontroller logic using the **Arduino IDE and Raspberry Pi Pico**.It provides a low-cost, scalable, and reliable security solution suitable for both real-world applications and academic projects.
