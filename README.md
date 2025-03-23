# PUC_v1 [![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
ESP32 Universal Controller with WebServer

## Description
PUC_v1 is an ESP32-based Universal Controller that features 4 analog controls, 8 digital buttons, and a simple battery percentage indicator. This controller operates in Wi-Fi AP mode and provides a web server-based interface, allowing users to control devices over a local network without requiring an internet connection.

## Screenshoot
![alt text](https://github.com/PrasZ24/PUC_v1/blob/main/Screenshoot/image.png?raw=true)

## Function Overview
`begin()` : Mandatory function in every project. Must be declared at the beginning of the program.
`setBatteryPin()` : To define which analog pins are connected to the battery voltage divider. Optional if battery percentage is not used.

