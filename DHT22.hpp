
#include "TemperatureSensor.hpp"


#define LOOP_TIME 10000


class DHT22 : public TemperatureSensor {
   public:
      DHT22(int pin) : TemperatureSensor(pin) {};
      ReadState read() override;
   private:
      enum BitState { LOGIC_0, LOGIC_1, BIT_READ_TIMEOUT };
      BitState readBit();
};