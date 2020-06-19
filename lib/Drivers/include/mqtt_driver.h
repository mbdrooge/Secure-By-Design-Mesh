#pragma once
#include <stdint.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MqttDriver
{
public:
    static MqttDriver &get_instance();
    MqttDriver(MqttDriver const &) = delete;
    void operator=(MqttDriver const &) = delete;
    ~MqttDriver() = default;

    void connect_send();
    void connect_receive(const std::string topic, void mqtt_callback(char *, uint8_t *, unsigned int));
    const bool publish(const std::string topic, const char *json);
    void loop();

private:
    MqttDriver() = default;
    WiFiClient wifi_client;
    PubSubClient mqtt_client;
    void reconnect_mqtt();
};