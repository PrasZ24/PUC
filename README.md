# PUC_v1 [![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
ESP32 Universal Controller with WebServer

## Description
PUC_v1 is an ESP32-based Universal Controller that features 4 analog controls, 8 digital buttons, and a simple battery percentage indicator. This controller operates in Wi-Fi AP mode and provides a web server-based interface, allowing users to control devices over a local network without requiring an internet connection.

## Screenshoot
![alt text](https://github.com/PrasZ24/PUC_v1/blob/main/Screenshoot/image.png?raw=true)

## Function Overview
`begin()`&nbsp;&nbsp;&nbsp;&nbsp; : Mandatory function in every project. Must be declared at the beginning of the program.<br/>
`setBatteryPin()` : To define which analog pins are connected to the battery voltage divider. Optional if battery percentage is not used.<br/>
`getLY()`         : Takes data from the left analog on the y-axis. Will return an integer value of -127 to 128.<br/>
`getLX()`         : Takes data from the left analog on the x-axis. Will return an integer value of -127 to 128.<br/>
`getRY()`         : Takes data from the right analog on the y-axis. Will return an integer value of -127 to 128.<br/>
`getRx()`         : Takes data from the right analog on the x-axis. Will return an integer value of -127 to 128.<br/>


