#include <Arduino.h>
#include <assert.h>
#include <constants.h>
#include "driver/hmac_sha256.h"

//TODO: reimplement in a sane way

// void assert_hmac_is_incorrect()
// {
//   //incorrect key to check hmac function. Key is padded to correct length by library
//   const char *incorrect_key = "INCORRECT_KEY";
//   MessageData data = MessageData("test_address", 0, 15, 50, 32, 32);
//   uint8_t data_array[DATA_SIZE_BYTES];
//   data.as_array(data_array);
//   uint8_t hash_array[HASH_SIZE_BYTES];
//   calculate_hmac_sha256(SECRET_KEY, hash_array, data_array);
//   //check validity using the wrong key to check validity --> hash is now incorrect. function returns false
//   assert(is_hmac_sha256_valid(incorrect_key, hash_array, data_array) == false);
// }

// void assert_hmac_is_correct()
// {
//   uint8_t hash_array[HASH_SIZE_BYTES];
//   MessageData data = MessageData("test_address", 0, 15, 50, 32, 32);
//   uint8_t data_array[DATA_SIZE_BYTES];
//   data.as_array(data_array);
//   calculate_hmac_sha256(SECRET_KEY, hash_array, data_array);

//   uint8_t hash_array2[HASH_SIZE_BYTES];
//   uint8_t data_array2[DATA_SIZE_BYTES];
//   data.as_array(data_array2);
//   MessageData data2 = MessageData("test_address", 0, 15, 50, 32, 32);
//   calculate_hmac_sha256(SECRET_KEY, hash_array2, data_array2);

//   assert(is_hmac_sha256_valid(SECRET_KEY, hash_array, data_array2) == true);
// }