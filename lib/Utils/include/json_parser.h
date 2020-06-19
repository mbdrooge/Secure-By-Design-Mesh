#pragma once
#include <ArduinoJson.h>
#include <message_data.h>
#include <constants.h>

class JsonParser
{
public:
    static JsonParser &get_instance();
    JsonParser(JsonParser const &) = delete;
    void operator=(JsonParser const &) = delete;
    ~JsonParser() = default;
    size_t write_json(const MessageData data);
    std::tuple<bool, MessageData> read_json(const char json[]);
    const std::string get_json();
    const bool is_read();
    const void set_read_state();

private:
    JsonParser() = default;
    String json;
    bool read_status = true;
};
