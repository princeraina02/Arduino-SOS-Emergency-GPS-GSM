# Arduino SOS Emergency System with GPS and GSM

This project creates an **SOS emergency system** using an **Arduino Nano**, a **GPS module** (e.g., NEO-6M), and a **GSM SIM900A module**. When activated via a button press, it sends an SMS with the user's GPS coordinates (latitude and longitude) to a predefined phone number, enabling quick location sharing during emergencies. The repository includes test codes to verify the functionality of the GPS and GSM modules.

## Features
- Sends GPS coordinates via SMS upon SOS button press.
- Lightweight and portable design using Arduino Nano.
- Includes test scripts for GPS and GSM module verification.

## Hardware Requirements
- Arduino Nano (or compatible microcontroller)
- GPS module (e.g., NEO-6M)
- GSM SIM900A module
- Push button (for SOS trigger)
- Jumper wires
- Power source (e.g., 9V battery or USB)
- Active SIM card with SMS capability

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)
- Libraries:
  - `TinyGPS++`: For parsing GPS data ([install via Arduino Library Manager](https://www.arduino.cc/en/Reference/Libraries) or [GitHub](https://github.com/mikalhart/TinyGPSPlus))
  - `SoftwareSerial`: Included with Arduino IDE

## Circuit Setup
1. **GPS Module**:
   - `VCC` to Arduino 3.3V/5V (check module specs)
   - `GND` to Arduino GND
   - `TX` to Arduino `D3`
   - `RX` to Arduino `D4`
2. **GSM SIM900A Module**:
   - `VCC` to external 5V power supply (or as per module requirements)
   - `GND` to Arduino GND
   - `TX` to Arduino `D7`
   - `RX` to Arduino `D8`
3. **SOS Button**:
   - Connect one pin to Arduino `D2`, the other to GND (use a pull-up resistor if needed).
4. Ensure proper power supply for the GSM module, as it may require more current than the Arduino can provide.

> **Note**: Verify pin assignments in the code, as they may vary. A schematic diagram is recommended for clarity (not included in this repo).

## Installation
1. Clone or download this repository:
   ```bash
   git clone https://github.com/princeraina02/Arduino-SOS-Emergency-GPS-GSM.git
