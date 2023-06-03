#include <stdint.h>
#include <Arduino.h>
#include "DHT22.hpp"


DHT22::BitState DHT22::readBit() {

  // Wait for line to go low
  int loopCnt = LOOP_TIME;
  while(digitalRead(sensorPin) == LOW)
    if (loopCnt-- == 0) return BIT_READ_TIMEOUT;

  // Start to measure time
  unsigned long t = micros();

  // Wait till line becomes high
  loopCnt = LOOP_TIME;
  while(digitalRead(sensorPin) == HIGH)
    if (loopCnt-- == 0) return BIT_READ_TIMEOUT;

  // If line was low for more than 40 ms, consider as logic 1 else logic 0
  return (micros() - t > 40) ? LOGIC_1 : LOGIC_0;
}

TemperatureSensor::ReadState DHT22::read() {
  // BUFFER TO RECEIVE
  uint8_t bits[5] = {0};
  uint8_t cnt = 7;
  uint8_t idx = 0;
  BitState bitBuf;

  // REQUEST SAMPLE
  // Request Method as described in datasheet
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(1100);  // Pulls down the line for 1ms
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(40); // Pulls up line for 40us
  pinMode(sensorPin, INPUT);

  // ACKNOWLEDGE or TIMEOUT
  if (readBit() == BIT_READ_TIMEOUT) return TEMP_ERROR_TIMEOUT;

  // READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
  for (int i=0; i<40; i++) {

    // Read single bit from line
    bitBuf = readBit();
    if (bitBuf == BIT_READ_TIMEOUT) return TEMP_ERROR_TIMEOUT;
    else if (bitBuf == LOGIC_1) bits[idx] |= (1 << cnt);  // Left shift to appropriate bit and store
    if (cnt == 0) {   // next byte?
      cnt = 7;    // restart at MSB
      idx++;      // next byte!
    }
    else cnt--;
  }

  // WRITE TO RIGHT VARS
  temperature = ((word)(bits[2] & 0x7F)) << 8 | bits[3];
  temperature *= 0.1;
  if (bits[2] & 0x80) temperature *= -1;

  uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];

  if (bits[4] != sum) return TEMP_ERROR_CHECKSUM;
  return TEMP_READ_OK;
}
