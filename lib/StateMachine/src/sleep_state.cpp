#include <Arduino.h>
#include "sleep_state.h"

void set_state_to_sleep()
{
  Serial.println("\r\nIn sleep state");
  delay(10000);
}