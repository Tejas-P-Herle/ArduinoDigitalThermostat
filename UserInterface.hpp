#include "Buttons.hpp"
#include "TemperatureSensor.hpp"
#include "TemperatureController.hpp"
#include "LiquidCrystal.h"


class UserInterface {
  public:
    UserInterface();
    void read();
    void show(TemperatureSensor tempSensor, TemperatureController tempController);
    void increaseTemp();
    void decreaseTemp();
    int getDesiredTemp();
  private:
    enum buttonNames { BTN_PLUS, BTN_MINUS };
    int buttonPins[2] = { 4, 3 };
    Buttons *buttons;

    LiquidCrystal *lcd;

    int desiredTemp = 25;
    int screenNo = 0;
    int screensCount = 3;
    int screenInterval = 1000;
};
