#pragma once
#include <SHA256.h>
#include <message_data.h>

//Test HMAC online should be the same when settings for input type and key type are TEXT and output type is HEX
//https://www.liavaag.org/English/SHA-Generator/HMAC/
inline void calculate_hmac_sha256(const char *key, uint8_t *hash_array, const MessageData *message_data)
{
    SHA256 sha;
    sha.resetHMAC(key, strlen(key));
    sha.update(message_data->get_data().c_str(), strlen(message_data->get_data().c_str()));
    sha.finalizeHMAC(key, strlen(key), hash_array, HASH_SIZE_BYTES);
    sha.clear();
}

//Check the message hash against the calculated hash.
//Returns true when message hash matches calculated hash.
inline bool is_hmac_sha256_valid(const char *key, uint8_t *original_hash, const MessageData *data)
{
    uint8_t new_hash[HASH_SIZE_BYTES];
    calculate_hmac_sha256(key, new_hash, data);
    for (int i = 0; i < HASH_SIZE_BYTES; i++)
    {
        if (original_hash[i] != new_hash[i])
        {
            return false;
        }
    }
    return true;
}

inline std::string get_hash_hex_string(uint8_t hash[HASH_SIZE_BYTES], const MessageData *message_data)
{
    std::string str;
    calculate_hmac_sha256(SECRET_KEY, hash, message_data);
    for (int i = 0; i < HASH_SIZE_BYTES; i++)
    {
        char temp[3];
        sprintf(temp, "%02X", hash[i]);
        str += temp;
    }
    return str;
}
