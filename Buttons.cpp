#include <Arduino.h>
#include "Buttons.hpp"



Buttons::Buttons(int *buttonPins) {
  // Save buttonPins as attribute
  pins = buttonPins;
}

void Buttons::initialize() {
  
  // Initalize all button pins as input pullup pins
  for (int i = 0; i < count; i++) {
    pinMode(pins[i], INPUT_PULLUP);
    callbacks[i] = NULL;
  }
}

void Buttons::setCallback(int buttonNo, voidFunction callback, void *obj) {

  // Store function to callback for a given button press
  callbacks[buttonNo] = callback;

  // Store object who's method should be called
  callbackObjs[buttonNo] = obj;
}

void Buttons::checkAll() {

  // Iterate over all buttons
  for (int i = 0; i < count; i++) {

    // Check if button is pressed(pin goes LOW)
    int pin = pins[i];
    if (digitalRead(pin) == LOW) {

      // If so, check if button is locked
      if (!lockedBtns[i]) {
        
        // Lock button to stop considering a single click as multiple clicks
        lockedBtns[i] = true;

        // If callback is set for button, then call it
        if (callbacks[i] != NULL) callbacks[i](callbackObjs[i]);
      }
    } else {
      // If button is now pressed, then remove lock
      lockedBtns[i] = false;
    }
  }
}

