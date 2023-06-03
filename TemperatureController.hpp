
class TemperatureController {
  public:
    TemperatureController(int fanPin, int heaterPin);

    enum SystemState { BOTH_OFF, FAN_ON, HEATER_ON };
    SystemState getState();

    void setFan(int state);
    void setHeater(int state);
    void update(int desiredTemp, int currentTemp);
  private:
    int fanPin, heaterPin;
    int isFanOn, isHeaterOn;
    float tolerance = 1;  // Tolerance between desired and measured temperature
};
