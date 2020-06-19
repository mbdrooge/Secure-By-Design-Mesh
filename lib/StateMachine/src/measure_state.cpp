#include <memory>
#include <Arduino.h>
#include <measurement.h>
#include "measure_state.h"

void set_state_to_measure(Bundle *bundle)
{
  Serial.println("\r\nIn measure state");
  Measurement mock = Measurement(45, 12, 21, 36);
  bundle->set_measurement(mock);
}