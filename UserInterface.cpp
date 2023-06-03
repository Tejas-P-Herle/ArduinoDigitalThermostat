#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include "UserInterface.hpp"


typedef void (UserInterface::*uiMethod) (void *obj);

char *ftostr(float num, int maxDigits, int decimals);
void increaseTempObj(void *obj);
void decreaseTempObj(void *obj);

UserInterface::UserInterface() {
  // Initalize all buttons and display
  buttons = new Buttons(buttonPins); 
  buttons->initialize();

  int rs = 12, en = 11, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
  lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
  lcd->begin(16, 2);

  // Run increaseTemp when BTN_PLUS is clicked
  buttons->setCallback(BTN_PLUS, &increaseTempObj, this);
  
  // Run decreaseTemp when BTN_MINUS is clicked
  buttons->setCallback(BTN_MINUS, &decreaseTempObj, this);
}


void UserInterface::read() {
  // Check all buttons and run appropriate callbacks if any buttons are pressed
  buttons->checkAll();
}


void UserInterface::show(TemperatureSensor tempSensor, TemperatureController tempController) {
  // Print Desired Temperature to first line
  char line[17];
  lcd->setCursor(0, 0);
  sprintf(line, "Des. Temp:%3dC", desiredTemp); 
  lcd->print(line);
  
  // Switch between temperature, fan state and heater state on second line
  // Store fan and heater state as a string
  String fanState;
  String heaterState;
  switch (tempController.getState()) {
    case tempController.FAN_ON: fanState = "ON";  heaterState = "OFF"; break;
    case tempController.HEATER_ON: heaterState = "ON"; fanState = "OFF"; break;
    case tempController.BOTH_OFF: fanState = "OFF"; heaterState = "OFF"; break;
  }

  // Determine screen to show based on time ellapsed
  screenNo = (millis() / screenInterval) % screensCount;
  switch (screenNo) {
    case 1: sprintf(line, "FAN:%s", fanState.c_str()); break;  // Show fan state when screen is 2
    case 2: sprintf(line, "HEATER:%s", heaterState.c_str()); break;  // Show heater state when screen is 3
    default: sprintf(line, "Temp:%sC", ftostr(tempSensor.get(), 5, 1));  // Show temperature when screen is 1
  }
  
  // Clear second Line
  lcd->setCursor(0, 1);
  lcd->print("                ");

  // Reset cursor and print line
  lcd->setCursor(0, 1);
  lcd->print(line);
}


void UserInterface::increaseTemp() { desiredTemp++; /* Increase Desired Temp */ }
void UserInterface::decreaseTemp() { desiredTemp--; /* Decrease Desired Temp */ }

int UserInterface::getDesiredTemp() { return desiredTemp;  /* Getter for Desired Temp */ }

void increaseTempObj(void *obj) { 
  // A wrapper function over increaseTemp which can be called with object reference
  UserInterface *uiObj = (UserInterface *)obj;
  uiObj->increaseTemp();
}

void decreaseTempObj(void *obj) {
  // A wrapper function over decreaseTemp which can be called with object reference
  UserInterface *uiObj = (UserInterface *)obj;
  uiObj->decreaseTemp();
}

char *ftostr(float num, int maxDigits, int decimals) {
  char str[100];

  dtostrf(num, maxDigits, decimals, str);
  return str;
}
