#include <Arduino.h>
#include "hmac_sha256.h"
#include "message_data.h"

MessageData::MessageData(const std::string sensor_addr, const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high) : sensor_address(sensor_addr), measurement_id(measurement_id), humidity(humidity), illuminance(illuminance), temperature_low(temperature_low), temperature_high(temperature_high)
{
    set_data(measurement_id, humidity, illuminance, temperature_low, temperature_high);
    calculate_hmac_sha256(SECRET_KEY, this->hash_array, this);
    this->hash = get_hash_hex_string(this->hash_array, this);
}
MessageData::MessageData(const std::string sensor_addr, const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high, uint8_t hash_array[HASH_SIZE_BYTES]) : sensor_address(sensor_addr), measurement_id(measurement_id), humidity(humidity), illuminance(illuminance), temperature_low(temperature_low), temperature_high(temperature_high)
{
    set_data(measurement_id, humidity, illuminance, temperature_low, temperature_high);
    std::copy(hash_array, hash_array + HASH_SIZE_BYTES, this->hash_array);
    this->hash = get_hash_hex_string(this->hash_array, this);
}

MessageData::MessageData(const MessageData &other) : sensor_address(other.sensor_address), measurement_id(other.measurement_id), humidity(other.humidity), illuminance(other.illuminance), temperature_low(other.temperature_low), temperature_high(other.temperature_high)
{
    set_data(other.measurement_id, other.humidity, other.illuminance, other.temperature_low, other.temperature_high);
    std::copy(std::begin(other.hash_array), std::end(other.hash_array), this->hash_array);
    this->hash = get_hash_hex_string(this->hash_array, this);
}

const uint8_t MessageData::get_humidity() const
{
    return this->humidity;
}

const uint8_t MessageData::get_illuminance() const
{
    return this->illuminance;
}

const uint8_t MessageData::get_temp_low() const
{
    return this->temperature_low;
}

const uint8_t MessageData::get_temp_high() const
{
    return this->temperature_high;
}

const std::string MessageData::get_sensor_address() const
{
    return this->sensor_address;
}

const unsigned long MessageData::get_measurement_id() const
{
    return this->measurement_id;
}

const std::string MessageData::get_hash() const
{
    return hash;
}

const uint8_t *MessageData::get_hash_array() const
{
    return hash_array;
}

const void MessageData::set_data(const unsigned long measurement_id, const uint8_t humidity, const uint8_t illuminance, const uint8_t temperature_low, const uint8_t temperature_high)
{
    uint8_t id_bytes[4];
    // convert from an unsigned long int to a 4-byte array
    id_bytes[0] = (uint8_t)((measurement_id >> 24) & 0xFF);
    id_bytes[1] = (uint8_t)((measurement_id >> 16) & 0xFF);
    id_bytes[2] = (uint8_t)((measurement_id >> 8) & 0XFF);
    id_bytes[3] = (uint8_t)((measurement_id & 0XFF));
    this->data_array[0] = id_bytes[0];
    this->data_array[1] = id_bytes[1];
    this->data_array[2] = id_bytes[2];
    this->data_array[3] = id_bytes[3];
    this->data_array[4] = humidity;
    this->data_array[5] = illuminance;
    this->data_array[6] = temperature_low;
    this->data_array[7] = temperature_high;
    char temp[24];
    sprintf(temp, "%02X|%02X|%02X|%02X|%02X|%02X|%02X|%02X",
            id_bytes[0],
            id_bytes[1],
            id_bytes[2],
            id_bytes[3],
            humidity,
            illuminance,
            temperature_low,
            temperature_high);
    this->data_string = temp;
}

const uint8_t *MessageData::get_data_array() const
{
    return this->data_array;
}

const std::string MessageData::get_data() const
{
    return this->data_string;
}

const void MessageData::print_message_data() const
{
    Serial.print("\r\n--Start Messagedata-- \r\n");
    Serial.print("Message ID: ");
    Serial.println(this->measurement_id);
    Serial.print("Temperature low: ");
    Serial.println(this->temperature_low);
    Serial.print("Temperature high: ");
    Serial.println(this->temperature_high);
    Serial.print("Humidity: ");
    Serial.println(this->humidity);
    Serial.print("Illuminance: ");
    Serial.println(this->illuminance);
    Serial.print("Data String: ");
    Serial.println(this->get_data().c_str());
    Serial.print("Data Array: ");
    for (int i = 0; i < DATA_SIZE_BYTES; i++)
    {
        Serial.print(this->data_array[i]);
        Serial.print(" ");
    }
    Serial.print("\r\nHash String: ");
    Serial.println(this->get_hash().c_str());
    Serial.print("Hash Array: ");
    for (int i = 0; i < DATA_SIZE_BYTES; i++)
    {
        Serial.print(this->hash_array[i]);
        Serial.print(" ");
    }
    Serial.println("\r\n--End Messagedata--\r\n");
}