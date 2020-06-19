#pragma once
#include <stdint.h>
class Measurement
{
public:
  Measurement(uint8_t humidity, uint8_t illuminance, uint8_t temperature_low, uint8_t temperature_high);
  Measurement(const Measurement &other);
  ~Measurement() = default;

  uint8_t get_humidity(void);
  uint8_t get_illuminance(void);
  uint8_t get_temp_low(void);
  uint8_t get_temp_high(void);

private:
  uint8_t humidity;
  uint8_t illuminance;
  uint8_t temperature_low;
  uint8_t temperature_high;
};
