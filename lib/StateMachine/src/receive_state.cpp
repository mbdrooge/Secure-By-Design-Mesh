#include <Arduino.h>
#include <xbee_driver.h>
#include <message_data.h>
#include <json_parser.h>
#include <bundle.h>
#include "measure_state.h"

void set_state_to_receive_coo()
{
    std::vector<uint8_t> rec;
    //add small delay
    bool status = XBeeDriver::get_instance().receive(&rec, 10);
    if (status)
    {
        uint8_t data[DATA_SIZE_BYTES] = {rec[0], rec[1], rec[2], rec[3], rec[4], rec[5], rec[6], rec[7]};
        uint8_t hash[HASH_SIZE_BYTES];
        for (int i = 0; i < HASH_SIZE_BYTES; i++)
        {
            hash[i] = rec[DATA_SIZE_BYTES + i];
        }

        Serial.println("Data:");
        for (uint i = 0; i < DATA_SIZE_BYTES; i++)
        {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        Serial.println("HASH:");
        for (uint i = 0; i < HASH_SIZE_BYTES; i++)
        {
            Serial.print(hash[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        unsigned long id = ((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + (data[3]));
        MessageData message_data = MessageData(XBeeDriver::get_instance().get_latest_address_string(), id, data[4], data[5], data[6], data[7], hash);
        message_data.print_message_data();
        JsonParser::get_instance().write_json(message_data);
    }
}