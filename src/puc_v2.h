#ifndef PUC_H
#define PUC_H

#include "Arduino.h"
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>

class puc {
public:
    puc();
    void begin(const char* ssid_name, const char* pw, IPAddress address);
    void DNS_RUN();
    bool device_status();
    int getLY();
    int getLX();
    int getRY();
    int getRX();
    int getButtonA();
    int getButtonB();
    int getButtonC();
    int getButtonD();


private:
    const char* ssid;
    const char* pw;
    IPAddress ip;
    IPAddress subnet = IPAddress(255, 255, 255, 0);
    IPAddress gateway = ip;
    AsyncWebServer server;
    DNSServer dnsServer;
    int lx_value, ly_value, rx_value, ry_value;
    int button_A_state, button_B_state, button_C_state, button_D_state;
};

#endif
