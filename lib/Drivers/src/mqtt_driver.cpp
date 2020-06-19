#include <constants.h>
#include "mqtt_driver.h"

MqttDriver &MqttDriver::get_instance()
{
    static MqttDriver instance;
    return instance;
}

void MqttDriver::connect_send()
{
    Serial.println("Connecting to MQTT...");
    this->mqtt_client.setClient(wifi_client);
    this->mqtt_client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    bool status = this->mqtt_client.connect(MQTT_USERNAME, MQTT_USERNAME, MQTT_PASSWORD);
    if (status)
    {
        Serial.println("Connected to MQTT");
    }
}

void MqttDriver::connect_receive(const std::string topic, void mqtt_callback(char *, uint8_t *, unsigned int))
{
    this->mqtt_client.subscribe(topic.c_str());
    this->mqtt_client.setCallback(mqtt_callback);
}

const bool MqttDriver::publish(const std::string topic, const char *json)
{
    Serial.println("\r\nPublishing to ");
    Serial.println(topic.c_str());
    return this->mqtt_client.publish(topic.c_str(), json);
}

void MqttDriver::reconnect_mqtt()
{
    Serial.println("Attempting to reconnect to mqtt");
    while (!this->mqtt_client.connected())
    {
        delay(200);
    }
    Serial.println("reconnected to mqtt!");
}

void MqttDriver::loop()
{
    if (!this->mqtt_client.connected())
    {
        reconnect_mqtt();
    }
    this->mqtt_client.loop();
}