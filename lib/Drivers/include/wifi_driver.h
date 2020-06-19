#pragma once
class WifiDriver
{
public:
    static WifiDriver &get_instance();
    WifiDriver(WifiDriver const &) = delete;
    void operator=(WifiDriver const &) = delete;
    ~WifiDriver() = default;
    void connect();

private:
    WifiDriver() = default;
    const char *ssid;
    const char *passwd;
};