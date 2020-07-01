#include <constants.h>
#include <message_data.h>
#include <hmac_sha256.h>
#include <xbee_driver.h>
#include <unity.h>

void assert_hmac_is_correct()
{
  uint8_t hash_array[HASH_SIZE_BYTES];
  MessageData data = MessageData("test_address", 0, 15, 50, 32, 32);
  calculate_hmac_sha256(SECRET_KEY, hash_array, &data);

  uint8_t hash_array2[HASH_SIZE_BYTES];
  MessageData data2 = MessageData("test_address", 0, 15, 50, 32, 32);
  calculate_hmac_sha256(SECRET_KEY, hash_array2, &data2);

  TEST_ASSERT_EQUAL(is_hmac_sha256_valid(SECRET_KEY, hash_array, &data2), true);
}

void assert_hmac_is_incorrect()
{
  //incorrect key to check hmac function. Key is padded to correct length by library
  const char *incorrect_key = "INCORRECT_KEY";
  MessageData data = MessageData("test_address", 0, 15, 50, 32, 32);
  uint8_t hash_array[HASH_SIZE_BYTES];
  calculate_hmac_sha256(SECRET_KEY, hash_array, &data);
  //check validity using the wrong key to check validity --> hash is now incorrect. function returns false
  TEST_ASSERT_EQUAL(is_hmac_sha256_valid(incorrect_key, hash_array, &data), false);
}

//Make sure the coordinator is up before running this test.
void test_xbee_driver_send()
{
  uint8_t data[DATA_SIZE_BYTES] = {12, 34, 10, 32, 21};
  bool send_status = XBeeDriver::get_instance().send(data, DATA_SIZE_BYTES);
  TEST_ASSERT_EQUAL(send_status, true);
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
  TEST_ASSERT_EQUAL(receive_status, true);
}

void setup()
{
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(assert_hmac_is_correct);
  RUN_TEST(assert_hmac_is_incorrect);
  // RUN_TEST(test_xbee_driver_send);
  UNITY_END();
}

void loop() {}