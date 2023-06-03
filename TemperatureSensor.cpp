
#include "TemperatureSensor.hpp"


TemperatureSensor::TemperatureSensor(int pin) {
  // Store sensorPin
  sensorPin = pin;
}

int TemperatureSensor::get() {
  // getter for temperature
  return temperature;
}
