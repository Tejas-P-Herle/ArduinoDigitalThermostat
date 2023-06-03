
#include "TemperatureSensor.hpp"


TemperatureSensor::TemperatureSensor(int pin) {
  // Store sensorPin
  sensorPin = pin;
}

float TemperatureSensor::get() {
  // getter for temperature
  return temperature;
}
