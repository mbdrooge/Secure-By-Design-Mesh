#include "xbee_driver.h"

XBeeDriver::XBeeDriver()
{
    this->xbee.begin(Serial);
    //delay to give xbee time to boot takes approx. 4 secs according to tests
    delay(5000);
    this->attached_addr = get_attached_address();
    print_status();
}

XBeeDriver &XBeeDriver::get_instance()
{
    static XBeeDriver instance;
    return instance;
}

const void XBeeDriver::print_status()
{
    Serial.println("\r\n\r\n--XBEE DRIVER SETUP--");
    Serial.print("XBee Address:\t");
    Serial.print("SH: ");
    Serial.print(this->attached_addr.getMsb(), HEX);
    Serial.print("\tSL: ");
    Serial.println(this->attached_addr.getLsb(), HEX);
    this->is_coordinator = xbee_is_coordinator();
    Serial.print("\r\nIs Coordinator: ");
    Serial.println(this->is_coordinator);
    Serial.println("--------------------------\r\n\r\n");
}

const XBeeAddress64 XBeeDriver::get_own_address()
{
    return this->attached_addr;
}

const std::string XBeeDriver::get_latest_address_string()
{
    return get_address_string(this->latest_source_addr);
}

const std::string XBeeDriver::get_address_string()
{
    return get_address_string(this->attached_addr);
}

const std::string XBeeDriver::get_address_string(XBeeAddress64 addr)
{
    String address_string = String(addr.getMsb(), HEX) + String(addr.getLsb(), HEX);
    return address_string.c_str();
}

const XBeeAddress64 XBeeDriver::get_latest_source_address()
{
    return this->latest_source_addr;
}

const bool XBeeDriver::send(XBeeAddress64 dest, uint8_t msg[], uint8_t message_length)
{
    ZBTxRequest req = ZBTxRequest(dest, &msg[0], message_length);
    ZBTxStatusResponse status = ZBTxStatusResponse();
    xbee.send(req);
    if (xbee.readPacket(500))
    {
        if (xbee.getResponse().isAvailable())
        {

            if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE)
            {
                xbee.getResponse().getZBTxStatusResponse(status);
                if (status.getDeliveryStatus() == SUCCESS)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

const bool XBeeDriver::send(uint8_t msg[], uint8_t message_length)
{
    XBeeAddress64 dest = XBeeAddress64(); //coordinator addr
    return send(dest, msg, message_length);
}

const bool XBeeDriver::receive(std::vector<uint8_t> *data, uint delay)
{
    if (xbee.readPacket(delay))
    {
        Rx64Response rx = Rx64Response();
        if (xbee.getResponse().isAvailable())
        {
            if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
            {
                xbee.getResponse().getZBRxResponse(rx);
                if (rx.isError())
                {
                    //error in received packet
                    return false;
                }
                else
                {
                    //valid packet received

                    auto frame_data = rx.getData();

                    //skip 1 because it contains garbage data.
                    for (int i = 1; i < rx.getDataLength(); i++)
                    {
                        data->push_back(frame_data[i]);
                    }
                    latest_source_addr = rx.getRemoteAddress64();
                    return true;
                }
            }
        }
    }
    //packet was not read.
    return false;
}

const bool XBeeDriver::send_at_command(uint8_t cmd[2], std::vector<uint8_t> *resp)
{
    AtCommandRequest req = AtCommandRequest();
    AtCommandResponse response = AtCommandResponse();
    req.setCommand(cmd);
    xbee.send(req);
    if (!xbee.readPacket(3000))
    {
        Serial.println("\r\nNo response when sending attached_address() request!");
        return false;
    }
    if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE)
    {
        xbee.getResponse().getAtCommandResponse(response);
        if (response.isOk())
        {
            //clear response vector of previous values
            resp->clear();
            uint8_t *frame_data = response.getFrameData();
            for (int i = 0; i < response.getFrameDataLength(); i++)
            {
                resp->push_back(frame_data[i]);
            }
            return true;
        }
        else if (response.isError())
        {
            Serial.print("\r\nError parsing AT Command Response: ");
            Serial.print(response.getErrorCode());
            return false;
        }
    }
    return false;
}

const XBeeAddress64 XBeeDriver::get_attached_address()
{
    uint8_t sh_cmd[2] = {'S', 'H'};
    uint32_t sh = 0;
    uint8_t sl_cmd[2] = {'S', 'L'};
    uint32_t sl = 0;
    std::vector<uint8_t> resp;
    bool command_status = send_at_command(sl_cmd, &resp);
    if (command_status)
    {
        sh = ((uint32_t)resp[7]) | ((uint32_t)resp[6] << 8) | ((uint32_t)resp[5] << 16) | ((uint32_t)resp[4] << 24);
    }
    command_status = send_at_command(sh_cmd, &resp);
    if (command_status)
    {
        sl = ((uint32_t)resp[7]) | ((uint32_t)resp[6] << 8) | ((uint32_t)resp[5] << 16) | ((uint32_t)resp[4] << 24);
    }
    if (sh == 0 || sl == 0)
    {
        //trigger watchdog for restart of chip.
        Serial.println("\r\nForcing restart, xbee driver could not get address!");
        while (true)
        {
            //trigger watchdog, wrong init of xbee driver. force restart
            //XBee did not reply to address request
        }
    }
    return XBeeAddress64(sl, sh);
}

const bool XBeeDriver::xbee_is_coordinator()
{
    uint8_t ce_cmd[2] = {'C', 'E'};
    std::vector<uint8_t> resp;
    bool command_sent = send_at_command(ce_cmd, &resp);
    if (command_sent)
    {
        return resp[4] == 1 ? true : false;
    }
    else
    {
        Serial.println("\r\nForcing restart, xbee driver could not get CE status!");
        while (true)
        {
            //trigger watchdog, wrong init of xbee driver. force restart
        }
    }
}
