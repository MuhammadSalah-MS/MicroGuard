# MicroGuard: Door Locker Security System

## Project Overview
MicroGuard is a door locker security system that allows users to unlock a door using a password. The project is implemented using two Atmega32 MCUs, each serving a specific role. The Human Machine Interface (HMI) is responsible for user interaction, taking inputs through a keypad, and displaying system responses and messages on a screen. The Control Unit manages all processing and decisions in the system, including password checking, door opening, and activating alarms.

## Architecture
The project follows a layered architecture model, consisting of Microcontroller Abstraction Layer (MCAL) and Hardware Abstraction Layer (HAL). The HMI layer includes LCD and keypad components implemented in HAL, as well as GPIO, UART, and Timer components in MCAL. The Control Unit layer comprises buzzer, EEPROM, DC-MOTOR components in HAL, and GPIO, I2C, UART, Timer, and PWM components in MCAL.

## System Sequence
1. **First-time Setup:**
   - The user needs to create a 5-character password when using the system for the first time.
   - The password is stored in EEPROM for later use.

2. **Logging In:**
   - Users can log in to the system using the previously created password.
   - The system provides an option to change the password.

3. **Incorrect Password Handling:**
   - If the user enters the wrong password, they have two chances to re-enter it.
   - After two consecutive incorrect attempts, the system enters alarm mode.

4. **Alarm Mode:**
   - In alarm mode, the system disables any further entries.
   - The buzzer is activated for a minute as alert.

## Implementation Details
- **HMI (Human Machine Interface):**
  - Keypad for user input.
  - LCD for displaying system responses and messages.

- **Control Unit:**
  - Buzzer for alarm activation.
  - EEPROM for password storage.
  - DC-MOTOR for controlling the door.

- **MCAL (Microcontroller Abstraction Layer):**
  - HMI MCAL Layer:
    - GPIO for general-purpose input/output.
    - UART for communication between the two MCUS.
    - Timer for timing-related functionalities.
  - Control Unit MCAL Layer:
    - GPIO general-purpose input/output.
    - I2C for communication with the EEPROM
    - UART for communication between the two MCUS.
    - Timer for timing-related functionalitites.
    - PWM for various control tasks.

## Images

## Getting Started
To use MicroGuard in your project, follow these steps:
1. Clone the repository: `git clone https://github.com/your-username/MicroGuard.git`
2. Connect the Atmega32 MCUs as per the provided schematics.
3. Upload the firmware to the respective MCUs using your preferred programming method.


## Acknowledgments
Special thanks to Eng. Moahmed Tarek for inspiration and guidance.

Feel free to contribute! If you encounter any issues or have suggestions, please open an issue on GitHub.
