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

    //Connect to the MQTT broker for sending only.
    //Uses credentials specified in Utils/constants.h
    void connect_send();

    //Connect to the MQTT broker for receiving only.
    //Uses credentials specified in Utils/constants.h
    //The specified callback is called when a MQTT message is received.
    void connect_receive(const std::string topic, void mqtt_callback(char *, uint8_t *, unsigned int));

    //Publish a message on the specified topic.
    //Returns publish status
    const bool publish(const std::string topic, const char *json);

    //Loops the mqtt driver and checks connected status.
    //This ensures continuous operation of the MQTT driver.
    void loop();

private:
    MqttDriver() = default;
    WiFiClient wifi_client;
    PubSubClient mqtt_client;
    void reconnect_mqtt();
};