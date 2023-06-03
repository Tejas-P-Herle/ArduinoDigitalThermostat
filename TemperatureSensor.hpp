
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TemperatureSensor {
  public:
    TemperatureSensor(int pin);

    enum ReadState { TEMP_READ_OK, TEMP_ERROR_CHECKSUM, TEMP_ERROR_TIMEOUT };

    int get();
    virtual ReadState read() { return TEMP_ERROR_TIMEOUT; };
  protected:
    int temperature;
    int sensorPin;
};

#endif
