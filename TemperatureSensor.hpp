
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TemperatureSensor {
  public:
    TemperatureSensor(int pin);

    enum ReadState { TEMP_READ_OK, TEMP_ERROR_CHECKSUM, TEMP_ERROR_TIMEOUT };

    float get();
    virtual ReadState read() { return TEMP_ERROR_TIMEOUT; };
  protected:
    float temperature;
    int sensorPin;
};

#endif
