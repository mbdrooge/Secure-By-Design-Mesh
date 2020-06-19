#pragma once
#include <vector>
#include <string>
#include <constants.h>
class MessageData
{
public:
    MessageData(const std::string sensor_addr, const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high);
    MessageData(const std::string sensor_addr, const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high, uint8_t hash_array[HASH_SIZE_BYTES]);
    MessageData(const MessageData &other);
    ~MessageData() = default;

    const unsigned long get_measurement_id() const;
    const uint8_t get_humidity() const;
    const uint8_t get_illuminance() const;
    const uint8_t get_temp_low() const;
    const uint8_t get_temp_high() const;
    const std::string get_sensor_address() const;
    const std::string get_hash() const;
    const uint8_t *get_hash_array() const;
    const std::string get_data() const;
    const uint8_t *get_data_array() const;
    const void print_message_data() const;

private:
    const std::string sensor_address;
    const unsigned long measurement_id;
    const uint8_t humidity;
    const uint8_t illuminance;
    const uint8_t temperature_low;
    const uint8_t temperature_high;
    std::string hash;
    std::string data_string;
    uint8_t hash_array[HASH_SIZE_BYTES];
    uint8_t data_array[DATA_SIZE_BYTES];
    const void set_data(const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high);
};