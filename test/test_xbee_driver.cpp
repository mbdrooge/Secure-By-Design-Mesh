#include <xbee_driver.h>
#include <Arduino.h>
#include <assert.h>
#include <constants.h>


void test_xbee_driver_send()
{
  uint8_t data[DATA_SIZE_BYTES] = {12, 34, 10, 32, 21};
  bool send_status = XBeeDriver::get_instance().send(data, DATA_SIZE_BYTES);
  Serial.print("\r\nSend Status: ");
  Serial.println(send_status);
  std::vector<uint8_t> response;
  bool receive_status = XBeeDriver::get_instance().receive(&response);
  Serial.print("\r\nReceive Status: ");
  Serial.println(receive_status);
  Serial.print("\r\nReceived message: ");
  for (auto c : response)
  {
    Serial.print(c);
    Serial.print(" ");
  }
  Serial.println();
}