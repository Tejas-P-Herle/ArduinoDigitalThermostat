#include <stdint.h>
#include "DHT11.hpp"
#include "UserInterface.hpp"


const int sensorPin = 2;
const int fanPin = 9;
const int heaterPin = 10;


DHT11 tempSensor(sensorPin);
TemperatureController tempController(fanPin, heaterPin);
UserInterface userInterface;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // Print blank Space after each loop
  Serial.println("");
  
  // Read temperature from sensor and handle error
  int readError;
  if (!(readError = tempSensor.read())) {
    Serial.print("Temp Read Error: ");
    switch (readError) {
      case tempSensor.TEMP_ERROR_CHECKSUM: Serial.println("CheckSum Error");
      case tempSensor.TEMP_ERROR_TIMEOUT: Serial.println("Timeout Error");
      default: Serial.println("Unknown Error");
    }
  }

  // Read userInterface buttons
  userInterface.read();

  // Show current state of program on LCD display
  userInterface.show(tempSensor, tempController);

  // Update fan and heater state based on desired and measured temperature
  tempController.update(userInterface.getDesiredTemp(), tempSensor.get());
  
  // Print Temperature to Serial Monitor
  Serial.print("Temperature(C): ");
  Serial.println(tempSensor.get());
}
