#include "puc.h"

puc::puc() : server(80) {
}

void puc::begin(const char* wifi_ssid, const char* wifi_pw, IPAddress wifi_address, bool toggle_battery) {
    ssid = wifi_ssid;
    pw = wifi_pw;
    ip = wifi_address;
    battery_state = toggle_battery;

    WiFi.softAP(ssid, pw);
    WiFi.softAPConfig(ip, gateway, subnet);
    Serial.println(WiFi.softAPIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", R"rawliteral(
            <!DOCTYPE html>
    <html>
        <head>
            <title>P-Universal Controller V1</title>
            <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0">
            <style>
                html, body {
                overscroll-behavior-y: contain;
                font-family:'Segoe UI', Tahoma, Geneva, Verdana, sans-serif
                user-select: none; /* Mencegah pemilihan teks */
                -webkit-user-select: none; /* Safari */
                -moz-user-select: none; /* Firefox */
                -ms-user-select: none; /* Internet Explorer/Edge */
                }
                input[type="range"] {
                appearance: none;
                -webkit-appearance: none;
                background-color: rgb(68, 11, 11);
                height: 3vw;
                width: 12vw;
                margin: 0;
                border-radius: 10vw;

                align-self: center;
                justify-self: center;

                box-shadow: 1px 0px 66px 9px rgba(0,0,0,1) inset;
                -webkit-box-shadow: 1px 0px 66px 9px rgba(0,0,0,1) inset;
                -moz-box-shadow: 1px 0px 66px 9px rgba(0,0,0,1) inset;
                }

                input[type="range"][orient="vertical"] {
                transform: rotate(270deg);
                width: 11vw;
                height: 3vw;
                }

                input[type="range"]::-webkit-slider-thumb {
                    appearance: none;
                    -webkit-appearance: none;

                    background-color: #f0f0f0;
                    box-shadow: inset 0px 0px 15px 10px rgba(0, 0, 0, 0.2);
                    width: 5.5vw;
                    height: 5.5vw;
                    border-radius: 100%;
                }

                .Text_frame {
                    display:grid;
                    margin-top: 2vw;
                }
                #t1 {
                    font-weight: bold;
                    font-size: 2.5vw;
                    justify-self: center;
                    margin: 0vw;
                }
                #t2 {
                    font-size: 1vw;
                    justify-self: center;
                    margin-top: 0.5vw;
                }
                .controller_frame {
                    display: flex;
                    justify-content: center;
                }
                .Left_frame {
                    display: grid;
                    border-radius: 4vw;
                    width: 18vw;
                    height: 18vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 5vw;
                    grid-template-rows:6vw 12vw;
                }
                .Middle_frame {
                    display: grid;
                    border-radius: 4vw;
                    width: 36vw;
                    height: 18vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 5vw;
                    grid-template-columns: 12vw 12vw 12vw;
                    grid-template-rows: 3.5vw 6vw 6vw;
                    justify-items: center;
                }
                #Battery_level {
                    justify-self: center;
                    font-size: 1.5vw;
                    font-weight: 500;
                    margin: 0vw;
                    margin-top: 0.8vw;
                    grid-column: 2/3;
                    grid-row: 1/2;
                }
                #box_a {
                    width: 4vw;
                    height: 2.5vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ff0000;
                    border-width: 0.2vw;
                    background-color: #f70e0e;
                    font-size: 1.5vw;
                    font-weight: 700;

                    grid-column: 1/2;
                    grid-row: 1/2;
                }
                #box_b {
                    width: 4vw;
                    height: 2.5vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ff0000;
                    border-width: 0.2vw;
                    background-color: #f70e0e;
                    font-size: 1.5vw;
                    font-weight: 700;

                    grid-column: 3/4;
                    grid-row: 1/2;
                }
                #box_1 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 1/2;
                    grid-row: 2/3;
                }
                #box_2 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 2/3;
                    grid-row: 2/3;
                }
                #box_3 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 3/4;
                    grid-row: 2/3;
                }
                #box_4 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 1/2;
                    grid-row: 3/4;
                }
                #box_5 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 2/3;
                    grid-row: 3/4;
                }
                #box_6 {
                    width: 6vw;
                    height: 4vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 0.7vw;
                    border-radius: 1vw;
                    border-color: #ffffff;
                    background-color: #ffffff;
                    font-size: 2vw;
                    font-weight: 700;

                    grid-column: 3/4;
                    grid-row: 3/4;
                }
                .Right_frame {
                    display: grid;
                    border-radius: 4vw;
                    width: 18vw;
                    height: 18vw;
                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    margin: 5vw;
                    grid-template-rows:6vw 12vw;
                }
                #Lx {
                    margin-bottom: 0.1  vw;
                    grid-column: 1/2;
                    grid-row: 1/2;
                }
                #Ly {
                    margin-bottom: 0.1vw;
                    grid-column: 1/2;
                    grid-row: 2/3;
                }
                #Rx {
                    margin-bottom: 0.1  vw;
                    grid-column: 1/2;
                    grid-row: 1/2;
                }
                #Ry {
                    margin-bottom: 0.1vw;
                    grid-column: 1/2;
                    grid-row: 2/3;
                }
            </style>
        </head>

        <body>
            <div class="Main_frame">
                <div class="Text_frame">
                    <p id="t1">P-Universal Controller</p>
                    <p id="t2">v1.0.0</p>
                </div>
                <div class="controller_frame">
                    <div class="Left_frame">
                        <input type="range" id="Lx" min="-128" max="127" ontouchend="reset('Lx')" onclick="reset('Lx')" oninput="sliderSendData('Lx')">
                        <input type="range" id="Ly" min="-128" max="127" orient="vertical" ontouchend="reset('Ly')"  onclick="reset('Ly')" oninput="sliderSendData('Ly')">
                    </div>
                    
                    <div class="Middle_frame">
                        <p id="Battery_level">
                            <pan id="Angka_baterai">100</pan>%
                        </p>
                        <button id="box_a" ontouchstart="buttonSendData('a', 1)" ontouchend="buttonSendData('a', 0)" onmousedown="buttonSendData('a', 1)" onmouseup="buttonSendData('a', 0)">A</button>
                        <button id="box_b" ontouchstart="buttonSendData('b', 1)" ontouchend="buttonSendData('b', 0)" onmousedown="buttonSendData('b', 1)" onmouseup="buttonSendData('b', 0)">B</button>

                        <button id="box_1" ontouchstart="buttonSendData('1', 1)" ontouchend="buttonSendData('1', 0)" onmousedown="buttonSendData('1', 1)" onmouseup="buttonSendData('1', 0)">1</button>
                        <button id="box_2" ontouchstart="buttonSendData('2', 1)" ontouchend="buttonSendData('2', 0)" onmousedown="buttonSendData('2', 1)" onmouseup="buttonSendData('2', 0)">2</button>
                        <button id="box_3" ontouchstart="buttonSendData('3', 1)" ontouchend="buttonSendData('3', 0)" onmousedown="buttonSendData('3', 1)" onmouseup="buttonSendData('3', 0)">3</button>
                        <button id="box_4" ontouchstart="buttonSendData('4', 1)" ontouchend="buttonSendData('4', 0)" onmousedown="buttonSendData('4', 1)" onmouseup="buttonSendData('4', 0)">4</button>
                        <button id="box_5" ontouchstart="buttonSendData('5', 1)" ontouchend="buttonSendData('5', 0)" onmousedown="buttonSendData('5', 1)" onmouseup="buttonSendData('5', 0)">5</button>
                        <button id="box_6" ontouchstart="buttonSendData('6', 1)" ontouchend="buttonSendData('6', 0)" onmousedown="buttonSendData('6', 1)" onmouseup="buttonSendData('6', 0)">6</button>

                    </div>  
                    <div class="Right_frame">
                        <input type="range" id="Rx" min="-128" max="127" ontouchend="reset('Rx')"  onclick="reset('Rx')" oninput="sliderSendData('Rx')">
                        <input type="range" id="Ry" min="-128" max="127" orient="vertical" ontouchend="reset('Ry')"  onclick="reset('Ry')" oninput="sliderSendData('Ry')">
                    </div>
                </div>
            </div>
            <script>
                function reset(slider) {
                    var range = document.getElementById(slider);
                    
                    if (parseInt(range.value) !== 0) { 
                        range.value = 0;
                        sliderSendData(slider);
                    }
                }
                function sliderSendData(sliderId) {
                    var xhttp = new XMLHttpRequest();
                    var value = document.getElementById(sliderId).value;

                    xhttp.open("POST", "/" + sliderId, true);
                    xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                    xhttp.send("value=" + value);
                }

                function buttonSendData(buttonId, state){
                    var xhttp = new XMLHttpRequest();

                    xhttp.open("POST", "/" + buttonId, true);
                    xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                    xhttp.send("state=" +state);
                }

                function updateBattery() {
                    var xhttp = new XMLHttpRequest();
                    xhttp.onreadystatechange = function() {
                        if (this.readyState == 4 && this.status == 200) {
                            document.getElementById("Angka_baterai").innerText = this.responseText;
                        }
                    };
                    xhttp.open("GET", "/getBattery", true);
                    xhttp.send();
                }
                setInterval(updateBattery, 2000);
            </script>
        </body>
    </html>
        )rawliteral");
    });

    server.on("/Ly", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("value", true)) {  // Periksa apakah ada parameter "value"
        int value = request->getParam("value", true)->value().toInt();
        ly_value = value;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/Lx", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("value", true)) {
        int value = request->getParam("value", true)->value().toInt();
        lx_value = value;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/Rx", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("value", true)) {
        int value = request->getParam("value", true)->value().toInt();
        rx_value = value;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/Ry", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("value", true)) {
        int value = request->getParam("value", true)->value().toInt();
        ry_value = value;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/a", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_A_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/b", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_B_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/1", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_1_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/2", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_2_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/3", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_3_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/4", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_4_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/5", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_5_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });
    server.on("/6", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
        int state = request->getParam("state", true)->value().toInt();
        button_6_state = state;
        request->send(200, "text/plain", "OK");
        } else {
        request->send(400, "text/plain", "Missing value");
        }
    });

    server.on("/", HTTP_GET, [this](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", "Welcome to P-Universal Controller!");
    });

    server.on("/getBattery", HTTP_GET, [this](AsyncWebServerRequest* request) {
        String batteryPercentage;
        if (battery_state){
            int batteryLevel = analogRead(pin_battery);
            batteryPercentage = String(map(batteryLevel, 0, 4095, 0, 100));
        } else {
            batteryPercentage = "none";
        }
        request->send(200, "text/plain", String(batteryPercentage));
    });

    server.begin();
}
void puc::setBatteryPin(int AnalogPin_battery){
    pin_battery = AnalogPin_battery;
}
int puc::getLY() { return ly_value; }
int puc::getLX() { return lx_value; }
int puc::getRY() { return ry_value; }
int puc::getRX() { return rx_value; }
int puc::getButtonA() { return button_A_state; }
int puc::getButtonB() { return button_B_state; }
int puc::getButton1() { return button_1_state; }
int puc::getButton2() { return button_2_state; }
int puc::getButton3() { return button_3_state; }
int puc::getButton4() { return button_4_state; }
int puc::getButton5() { return button_5_state; }
int puc::getButton6() { return button_6_state; }
