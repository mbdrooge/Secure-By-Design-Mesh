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

    //Returns the XBeeAddress64 of the connected XBee unit.
    const XBeeAddress64 get_own_address();

    //Returns the address string of the connected XBee unit.
    const std::string get_address_string();

    //Returns the XBeeAddress64 of the most recent incoming message.
    const XBeeAddress64 get_latest_source_address();

    //Returns the address string of the most recent incoming message.
    const std::string get_latest_address_string();

    //Returns connected XBee unit CE status as boolean
    const bool xbee_is_coordinator();

    //Send message using connected XBee unit. When no address is specified, the Coordinator address is used.
    const bool send(std::vector<uint8_t> *msg, std::vector<uint8_t> *resp);
    const bool send(XBeeAddress64 dest, uint8_t msg[], uint8_t message_length);
    const bool send(uint8_t msg[], uint8_t message_length);

    //Receive message using connected XBee unit.
    //Beware: delay(ms) should be > 0
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