#ifndef PUC_H
#define PUC_H

#include "Arduino.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class puc {
public:
    puc();
    void begin(const char* ssid_name, const char* pw, IPAddress address, bool toggle_battery);
    void setBatteryPin(int AnalogPin_battery);
    int getLY();
    int getLX();
    int getRY();
    int getRX();
    int getButtonA();
    int getButtonB();
    int getButton1();
    int getButton2();
    int getButton3();
    int getButton4();
    int getButton5();
    int getButton6();

private:
    const char* ssid;
    const char* pw;
    IPAddress ip;
    IPAddress subnet = IPAddress(255, 255, 255, 0);
    IPAddress gateway = IPAddress(192, 168, 4, 1);
    AsyncWebServer server;
    int lx_value, ly_value, rx_value, ry_value;
    int button_A_state, button_B_state, button_1_state, button_2_state;
    int button_3_state, button_4_state, button_5_state, button_6_state;
    int pin_battery;
    bool battery_state = true;
};

#endif
