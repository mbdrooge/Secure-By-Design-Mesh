#include "measurement.h"

Measurement::Measurement(uint8_t humidity, uint8_t illuminance, uint8_t temperature_low, uint8_t temperature_high) : humidity(humidity), illuminance(illuminance), temperature_low(temperature_low), temperature_high(temperature_high) {}

Measurement::Measurement(const Measurement &other) : humidity(other.humidity), illuminance(other.illuminance), temperature_low(other.temperature_low), temperature_high(other.temperature_high) {}

uint8_t Measurement::get_humidity(void)
{
  return this->humidity;
}

uint8_t Measurement::get_illuminance(void)
{
  return this->illuminance;
}

uint8_t Measurement::get_temp_low()
{
  return this->temperature_low;
}

uint8_t Measurement::get_temp_high()
{
  return this->temperature_high;
}