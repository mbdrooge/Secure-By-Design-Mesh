#include <ESP8266WiFi.h>
#include <constants.h>
#include "wifi_driver.h"

WifiDriver &WifiDriver::get_instance()
{
    static WifiDriver instance;
    return instance;
}

void WifiDriver::connect()
{
    this->ssid = WIFI_SSID;
    this->passwd = WIFI_PASSWORD;
    WiFi.begin(this->ssid, this->passwd);
    //small wait to allow wifi to start
    delay(1000);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
    Serial.println("\r\nConnecting");
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
        Serial.println("WiFi Connected!");
        Serial.println("\r\nConnected!");
        Serial.print("Using IP-Address: ");
        Serial.println(WiFi.localIP());
    }
}