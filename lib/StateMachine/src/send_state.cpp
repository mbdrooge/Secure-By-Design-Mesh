#include <Arduino.h>
#include <XBee.h>
#include <send_state.h>
#include <mqtt_driver.h>
#include <xbee_driver.h>
#include <measurement.h>
#include <json_parser.h>
#include <hmac_sha256.h>
#include <bundle.h>

void set_state_to_send(Bundle *bundle)
{
  Serial.println("\r\nIn send state");
  if (!bundle->contains_measurement())
  {
    Serial.println("\r\nError: Measurement was not found in bundle!\r\n");
    return;
  }

  //collect all the data needed to send a message
  std::string address_string = XBeeDriver::get_instance().get_address_string();
  unsigned long id = bundle->get_measurement_count();
  uint8_t hum = bundle->get_measurement().get_humidity();
  uint8_t ill = bundle->get_measurement().get_illuminance();
  uint8_t temperature_low = bundle->get_measurement().get_temp_low();
  uint8_t temperature_high = bundle->get_measurement().get_temp_high();
  const MessageData data = MessageData(address_string, id, hum, ill, temperature_low, temperature_high);
  //create the message
  uint8_t message[DATA_SIZE_BYTES + HASH_SIZE_BYTES];
  std::copy(data.get_data_array(), data.get_data_array() + DATA_SIZE_BYTES, message);
  std::copy(data.get_hash_array(), data.get_hash_array() + HASH_SIZE_BYTES, message + DATA_SIZE_BYTES);

  XBeeDriver::get_instance().send(message, DATA_SIZE_BYTES + HASH_SIZE_BYTES);
  data.print_message_data();
  bundle->increase_measurement_count();
}

void set_state_to_send_coo()
{
  if (!JsonParser::get_instance().is_read())
  {
    const std::string combined_topic = MQTT_BASE_TOPIC + "00" +
                                       XBeeDriver::get_instance().get_latest_address_string();
    bool status = MqttDriver::get_instance()
                      .publish(combined_topic, JsonParser::get_instance().get_json().c_str());
    JsonParser::get_instance().set_read_state();
    Serial.print("Publish status: ");
    Serial.println(status);
  }
}