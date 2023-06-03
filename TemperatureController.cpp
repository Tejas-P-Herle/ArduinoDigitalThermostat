
#include <Arduino.h>
#include "TemperatureController.hpp"


TemperatureController::TemperatureController(int fanPin, int heaterPin) {

  // Store pin numbers and set them as output
  this->fanPin = fanPin;
  this->heaterPin = heaterPin;

  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
}

TemperatureController::SystemState TemperatureController::getState() {

  // Get state of fan and heater
  if (isFanOn) return FAN_ON;
  if (isHeaterOn) return HEATER_ON;
  return BOTH_OFF;
}

void TemperatureController::update(int desiredTemp, int currentTemp) {

  // Update fan and heater state based on desired and current temp
  if (abs(desiredTemp - currentTemp) < tolerance) {

    // If desired and current temp is close enough then don't switch on anything
    setFan(LOW);
    setHeater(LOW);
  } else if (desiredTemp > currentTemp) {

    // If desired temp is higher then turn on heater and turn off fan
    setFan(LOW);
    setHeater(HIGH);
  } else if (desiredTemp < currentTemp) {

    // If desired temp is lower then turn on fan and turn off heater
    setFan(HIGH);
    setHeater(LOW);
  }
}

void TemperatureController::setFan(int state) {
  if (state) {
    // Set fan on flag and write HIGH to fanPin
    isFanOn = 1;
    digitalWrite(fanPin, HIGH);
  } else {
    // Set fan off flag and write LOW to fanPin
    isFanOn = 0;
    digitalWrite(fanPin, LOW);    
  }
}
void TemperatureController::setHeater(int state) {
  if (state) {
    // Set heater on flag and write HIGH to heaterPin
    isHeaterOn = 1;
    digitalWrite(heaterPin, HIGH);
  } else {
    // Set heater off flag and write LOW to heaterPin
    isHeaterOn = 0;
    digitalWrite(heaterPin, LOW);
  }
}
