#include <message_data.h>
#include <hmac_sha256.h>
#include "json_parser.h"

JsonParser &JsonParser::get_instance()
{
    static JsonParser instance;
    return instance;
}

const void JsonParser::set_read_state()
{
    this->read_status = true;
    this->json.clear();
}

const bool JsonParser::is_read()
{
    return this->read_status;
}

size_t JsonParser::write_json(const MessageData data)
{
    StaticJsonDocument<JSON_DOC_CAP> doc;
    doc["sensorAddr"] = data.get_sensor_address().c_str();
    doc["messageCount"] = data.get_measurement_id();
    doc["data"] = data.get_data().c_str();
    doc["hash"] = data.get_hash().c_str();
    //set read status to false so new message can be read.
    this->read_status = false;
    return serializeJson(doc, this->json);
}

const std::string JsonParser::get_json()
{
    return this->json.c_str();
}

// std::tuple<bool, MessageData> read_json(const char json[])
// {
//     //TODO: fix sensor address
//     const std::string SENSOR_ADDRESS = "test_sensor";
//     StaticJsonDocument<JSON_DOC_CAP> doc;
//     std::tuple<bool, MessageData> return_value = std::make_tuple(false, MessageData(SENSOR_ADDRESS, 0, 0, 0, 0, 0, 0));
//     DeserializationError error = deserializeJson(doc, json);
//     if (error)
//     {
//         Serial.print(F("deserializeJson() failed: "));
//         Serial.println(error.c_str());
//         return return_value;
//     }
//     const char *sensorAddr = doc["sensorAddr"];
//     int messageCount = doc["messageCount"];
//     int messageLength = doc["messageLength"];
//     JsonArray data = doc["data"].as<JsonArray>();
//     JsonArray hash = doc["hash"].as<JsonArray>();

//     std::vector<const char *> dataList;
//     std::vector<int> hashList;

//     Serial.print("\r\n\r\nSensorAddress: ");
//     Serial.println(sensorAddr);
//     Serial.print("MessageCount: ");
//     Serial.println(messageCount);
//     Serial.print("Message Length: ");
//     Serial.println(messageLength);

//     //fill vectors with data from json
//     for (JsonVariant v : data)
//     {
//         dataList.insert(dataList.end(), v.as<char *>());
//     }
//     for (JsonVariant v : hash)
//     {
//         hashList.insert(hashList.end(), v.as<int>());
//     }

//     Serial.print("Data array: ");
//     for (uint i = 0; i < dataList.size(); i++)
//     {
//         Serial.print(*dataList[i]);
//     }
//     Serial.print("\r\nHash: ");
//     for (uint i = 0; i < hashList.size(); i++)
//     {
//         Serial.print(hashList[i]);
//         Serial.print(" ");
//     }
//     //TODO: add measurement id
//     MessageData message_data = MessageData(sensorAddr, 0,  *dataList[0], *dataList[1], *dataList[2], *dataList[3], *dataList[4]);
//     return_value = std::make_tuple(true, message_data);
//     return return_value;
// }
