# PUC_v1 [![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/) ![GitHub Release](https://img.shields.io/github/v/release/PrasZ24/PUC_v1)


ESP32 Universal Controller with WebServer

## Description
<p align="justify">
PUC_v1 is an ESP32-based Universal Controller that features 4 analog controls, 8 digital buttons, and a simple battery percentage indicator. This controller operates in Wi-Fi AP mode and provides a web server-based interface, allowing users to control devices over a local network without requiring an internet connection. This library uses another library : <code>WiFi.h</code>, <code>AsyncTCP.h</code>, and <code>ESPAsyncWebServer.h</code>. So make sure it is installed if an error occurs.<br/><br/></p>
:speech_balloon: Feedback is very much expected for the development of this library.

## Screenshoot
![Demo screenshoot](https://github.com/PrasZ24/PUC_v1/blob/main/Screenshoot/image.png?raw=true)

## Function Overview
`begin()` : Mandatory function in every project. Must be declared at the beginning of the program.<br/>
`setBatteryPin()` : To define which analog pins are connected to the battery voltage divider. Optional if battery percentage is not used.<br/><br/>
`getLY()` : Takes data from the left analog on the y-axis. Will return an integer value of -127 to 128.<br/>
`getLX()` : Takes data from the left analog on the x-axis. Will return an integer value of -127 to 128.<br/>
`getRY()` : Takes data from the right analog on the y-axis. Will return an integer value of -127 to 128.<br/>
`getRx()` : Takes data from the right analog on the x-axis. Will return an integer value of -127 to 128.<br/><br/>
`getButtonA()` : Gets the boolean value of the A button. Returns a value of 1 or 0.<br/>
`getButtonB()` : Gets the boolean value of the B button. Returns a value of 1 or 0. <br/>
`getButton1()` : Gets the boolean value of the 1 button. Returns a value of 1 or 0. <br/>
`getButton2()` : Gets the boolean value of the 2 button. Returns a value of 1 or 0. <br/>
`getButton3()` : Gets the boolean value of the 3 button. Returns a value of 1 or 0. <br/>
`getButton4()` : Gets the boolean value of the 4 button. Returns a value of 1 or 0. <br/>
`getButton5()` : Gets the boolean value of the 5 button. Returns a value of 1 or 0. <br/>
`getButton6()` : Gets the boolean value of the 6 button. Returns a value of 1 or 0. <br/>

## :warning: Warning and Limitation
* Use landscape mode for better viewing
* Large flash-size uses!
 

