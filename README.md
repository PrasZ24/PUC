# PUC_v1
ESP32 Universal Controller with WebServer

## Description
PUC_v1 is an ESP32-based Universal Controller that features 4 analog controls, 8 digital buttons, and a simple battery percentage indicator. This controller operates in Wi-Fi AP mode and provides a web server-based interface, allowing users to control devices over a local network without requiring an internet connection.

## Screenshoot
![alt text](https://github.com/PrasZ24/PUC_v1/blob/main/Screenshoot/image.png?raw=true)

## Function Overview
`begin(char* wifi_ssid, char* wifi_pw, IPAddress wifi_address, bool toggle_battery)` : Mandatory function in every project. Must be declared at the beginning of the program.

