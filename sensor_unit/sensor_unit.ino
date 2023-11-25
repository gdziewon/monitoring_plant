#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

// Pins //
const int moistureSensorPin = A0;
const int lightSensorPin = A1;

// Variables for calculating the average //
const int numReadings = 5;
int moistureReadings[numReadings];
int lightReadings[numReadings];
int readIndex = 0;
int totalMoisture = 0;
int totalLight = 0;
int averageMoisture = 0;
int averageLight = 0;

// Values needed for mapping //
int dryValue = 180;
int wetValue = 0;
int brightValue = 500;
int darkValue = 30;

// Variables for sending //
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 5000;

void setup() {
  rf_driver.init(); // Initializing the RF communication driver

  // Initializing arrays
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    moistureReadings[thisReading] = 0;
    lightReadings[thisReading] = 0;
  }
}

void loop() {

  // Replacing the oldest reading with a new one and incrementing the read index
  totalMoisture -= moistureReadings[readIndex];
  totalLight -= lightReadings[readIndex];
  moistureReadings[readIndex] = analogRead(moistureSensorPin);
  lightReadings[readIndex] = analogRead(lightSensorPin);
  totalMoisture += moistureReadings[readIndex];
  totalLight += lightReadings[readIndex];

  readIndex++;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calculating averages
  averageMoisture = totalMoisture / numReadings;
  averageLight = totalLight / numReadings;

  // Check if it's time to send
  if (millis() - lastPrintTime >= printInterval) {

    // Scaling values
    int moistureLevel = 9 - map(averageMoisture, wetValue, dryValue, 0, 9);
    moistureLevel = constrain(moistureLevel, 0, 9);
    int lightLevel = map(averageLight, darkValue, brightValue, 0, 9);
    lightLevel = constrain(lightLevel, 0, 9);

    // Preparing the message to be sent
    char msg[4];
    sprintf(msg, "%1d %1d", moistureLevel, lightLevel);

    // Sending the message via RF
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();

    lastPrintTime = millis();
  }

  delay(1000);
}
