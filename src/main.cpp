#include <Arduino.h>
#include <SHA256.h>
#include <state_machine_coordinator.h>
#include <state_machine_end_node.h>
#include <xbee_driver.h>
#include <mqtt_driver.h>
#include <wifi_driver.h>

bool is_coordinator;

//Please make sure to specify your settings in the Utils/constants.h file before running.
void setup()
{
  Serial.begin(9600);

  if (XBeeDriver::get_instance().xbee_is_coordinator())
  {
    WifiDriver::get_instance().connect();
    MqttDriver::get_instance().connect_send();
    StateMachineCoordinator::get_instance();
    is_coordinator = true;
  }
  else
  {
    StateMachineEndNode::get_instance();
    is_coordinator = false;
  }
}

void loop()
{
  if (is_coordinator)
  {
    StateMachineCoordinator::get_instance().loop();
  }
  else
  {
    StateMachineEndNode::get_instance().loop();
  }
}