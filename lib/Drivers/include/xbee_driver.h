#pragma once
#include <XBee.h>
#include <constants.h>
class XBeeDriver
{
public:
    static XBeeDriver &get_instance();
    XBeeDriver(XBeeDriver const &) = delete;
    void operator=(XBeeDriver const &) = delete;
    ~XBeeDriver() = default;

    const XBeeAddress64 get_own_address();
    const XBeeAddress64 get_latest_source_address();
    const std::string get_latest_address_string();
    const std::string get_address_string();
    const bool xbee_is_coordinator();
    const bool send(std::vector<uint8_t> *msg, std::vector<uint8_t> *resp);
    const bool send(XBeeAddress64 dest, uint8_t msg[], uint8_t message_length);
    const bool send(uint8_t msg[], uint8_t message_length);
    const bool receive(std::vector<uint8_t> *data, uint delay = 1000);

private:
    XBeeAddress64 attached_addr;
    bool is_coordinator;
    XBee xbee = XBee();
    XBeeAddress64 latest_source_addr;
    XBeeDriver();
    const void print_status();
    const XBeeAddress64 get_attached_address();
    const std::string get_address_string(XBeeAddress64 address);
    const bool send_at_command(uint8_t cmd[2], std::vector<uint8_t> *resp);
};