# Remote Plant Monitoring System

This Arduino-based system is designed to monitor soil moisture and light levels for optimal plant care. It comprises a sensor unit for data acquisition and a display unit for user interaction.

## Project Overview

The Remote Plant Monitoring System features:
- **Soil Moisture Sensing**: Using a custom sensor made from nails.
- **Light Level Monitoring**: Employing a photoresistor.
- **Wireless Communication**: 433MHz RF modules transmit data between units.
- **User-Friendly Interface**: A 7-segment display alternates between moisture and light readings with LED indicators.

## Hardware Components

### Sensor Unit
- **Arduino Uno**: Manages sensor readings and wireless communication.
- **Sensors**: 
  - Soil Moisture Sensor (DIY using nails)
  - Light Sensor (Photoresistor)
- **RF Transmission Module**: 433MHz

### Display Unit
- **Arduino Uno**: Receives and processes data.
- **Display**: 7-Segment LED
- **Indicators**: Blue and Yellow LEDs
- **RF Reception Module**: 433MHz

## Software Dependencies

- [Arduino IDE](https://www.arduino.cc/en/Main/Software)
- [RadioHead Library](http://www.airspayce.com/mikem/arduino/RadioHead/)

- ## Schematics

### Sensor Unit Schematic
- **Arduino Uno**
  - A0: Connected to one nail of the soil moisture sensor.
  - GND: Connected to the other nail of the soil moisture sensor.
  - A1: Connected to one leg of the photoresistor.
  - 5V: Connected to the other leg of the photoresistor through a 10kΩ resistor.
  - Digital Pins (As per RF module requirements): Connected to the 433MHz RF transmission module.

### Display Unit Schematic
- **Arduino Uno**
  - Pins 2-8: Connected to the 7-segment display.
  - Pin 12: Connected to the blue LED through a 220Ω resistor.
  - Pin 10: Connected to the yellow LED through a 220Ω resistor.
  - GND: Connected to the common ground of the LEDs.
  - Digital Pins (As per RF module requirements): Connected to the 433MHz RF reception module.
