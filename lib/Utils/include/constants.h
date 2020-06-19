#pragma once
#include <stdint.h>
#include <ArduinoJson.h>

//HMAC
//size of the hash used to calculate the HMAC
const uint8_t HASH_SIZE_BYTES = 32;

const char *const BASE_KEY = "VeRy sEcReT";
const char *const SENSOR_ID = "123456";
//base key + sensor id seperate by a single space
const char *const SECRET_KEY = "VeRy sEcReT 123456";

//MQTT
//specify the mqtt base topic here. The specific IEEE64 address of the message source is appended to the base topic
const std::string MQTT_BASE_TOPIC = "/sensors/";

//Specify the specific port used by your MQTT server.
const uint16_t MQTT_SERVER_PORT = 1883;

//MQTT username, leave as empty string when username is not used
const char *const MQTT_USERNAME = "---";

//MQTT password, leave as empty string when password is not used
const char *const MQTT_PASSWORD = "---";

//WIFI
const char *const WIFI_SSID = "---";
const char *const WIFI_PASSWORD = "---";
const char *const MQTT_SERVER_IP = "---";

//DataMessage
//Default size of the datamessage is 8 bytes
const uint8_t DATA_SIZE_BYTES = 8;

//JSON parser
//Reserve 255 bytes in json for every data entry
const int JSON_DOC_CAP = JSON_OBJECT_SIZE(DATA_SIZE_BYTES * 255);