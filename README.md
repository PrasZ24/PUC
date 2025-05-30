# PUC_v2 [![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/) ![GitHub Release](https://img.shields.io/github/v/release/PrasZ24/PUC_v1)


ESP32 Universal Controller with WebServer

## Description

PUC_v2 is an ESP32-based Universal Controller that features 2 joystick controls and 4 digital buttons.

This controller operates in **Wi-Fi AP mode** and provides a **web server-based interface**, allowing users to control devices over a local network without requiring an internet connection.

This library uses the following libraries, so make sure they are installed:
- `WiFi.h` (built-in on ESP32 core)
- `DNSServer.h` (built-in on ESP32 core)
- [`AsyncTCP.h`](https://github.com/ESP32Async/AsyncTCP)
- [`ESPAsyncWebServer.h`](https://github.com/ESP32Async/ESPAsyncWebServer)

:speech_balloon: Feedback is very much expected for the development of this library.


## Screenshoot
![Demo screenshoot](https://github.com/PrasZ24/PUC_v1/blob/main/Screenshoot/PUC_v2.jpg)

## Function Overview
`begin()` : Mandatory function in every project. Must be declared at the beginning of the program.<br/>
`device_status` : Get status if any devices connected to Wifi. Will return an boolean, <code>true</code> when any connected and <code>false</code> when no one device connected.<br/></br>
`getLY()` : Takes data from the left joystick on the y-axis. Will return an integer value of -127 to 128.<br/>
`getLX()` : Takes data from the left joystick on the x-axis. Will return an integer value of -127 to 128.<br/>
`getRY()` : Takes data from the right joystick on the y-axis. Will return an integer value of -127 to 128.<br/>
`getRx()` : Takes data from the right joystick on the x-axis. Will return an integer value of -127 to 128.<br/><br/>
`getButtonA()` : Gets the boolean value of the A button. Returns a value of 1 or 0.<br/>
`getButtonB()` : Gets the boolean value of the B button. Returns a value of 1 or 0. <br/>
`getButtonC()` : Gets the boolean value of the C button. Returns a value of 1 or 0. <br/>
`getButtonD()` : Gets the boolean value of the D button. Returns a value of 1 or 0. <br/>


## :warning: Warning and Limitation
* Use landscape mode!
* Large flash-size usage!
 

