#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

// Pins //
const int displayPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int decimalPoint = 9;
const int blueLED = 12;
const int yellowLED = 10;

// Array values for LED //
byte displayLEDs[10][7] = { 
        { 0,0,0,0,0,0,1 },  // = 0
        { 1,0,0,1,1,1,1 },  // = 1
        { 0,0,1,0,0,1,0 },  // = 2
        { 0,0,0,0,1,1,0 },  // = 3
        { 1,0,0,1,1,0,0 },  // = 4
        { 0,1,0,0,1,0,0 },  // = 5
        { 0,1,0,0,0,0,0 },  // = 6
        { 0,0,0,1,1,1,1 },  // = 7
        { 0,0,0,0,0,0,0 },  // = 8
        { 0,0,0,0,1,0,0 }   // = 9     
        }; 

bool displayMoisture = true; // Variable to switch between moisture and light

void setup() {
  rf_driver.init(); // Initializing the RF communication driver

  // Initializing display pins
  for (int i = 0; i < 7; i++) {
    pinMode(displayPins[i], OUTPUT);
  }
  pinMode(decimalPoint, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
}

// Displaying a number
void displayNumber(int number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], displayLEDs[number][i]);
  }
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  // Checking if a message is received
  if (rf_driver.recv(buf, &buflen)) {
    // Checking message length
    if (buflen == 3) {
      buf[buflen] = '\0';
      String receivedMsg = String((char*)buf);

      // Extracting values from the message
      int moistureValue = receivedMsg.charAt(0) - '0';
      int lightValue = receivedMsg.charAt(2) - '0';

      // Switching display between moisture and light
      displayMoisture = !displayMoisture;

      // Displaying the appropriate value and controlling LEDs
      if (displayMoisture) {
        displayNumber(moistureValue);
        digitalWrite(blueLED, HIGH);
        digitalWrite(yellowLED, LOW);
      } else {
        displayNumber(lightValue);
        digitalWrite(blueLED, LOW);
        digitalWrite(yellowLED, HIGH);
      }
    }
  }
}
