#include "puc_v2.h"

puc::puc() : server(80) {
}

void puc::begin(const char* wifi_ssid, const char* wifi_pw, IPAddress wifi_address) {
    ssid = wifi_ssid;
    pw = wifi_pw;
    ip = wifi_address;

    WiFi.softAP(ssid, pw);
    WiFi.softAPConfig(ip, ip, subnet); // Gateway = IP ESP32
    WiFi.setTxPower(WIFI_POWER_13dBm);
    dnsServer.start(53, "*", WiFi.softAPIP());

    Serial.print("IP ADDRESS ESP32 : ");
    Serial.println(WiFi.softAPIP());

    // Halaman utama
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", R"rawliteral(
            <!DOCTYPE html>
            <html lang="id">
            <head>
                <meta charset="UTF-8" />
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
                <title>P-Universal Controller V1</title>
                <style>
                body {
                    margin: 0;
                    height: 100vh;
                    overflow: hidden;
                    position: relative;
                    background: #e7e7e7;
                    display: flex;
                    flex-direction: column;
                    justify-content: center;
                    align-items: center;
                    touch-action: none;
                }

                body::before {
                    content: "";
                    position: absolute;
                    inset: 0;
                    background: linear-gradient(120deg, #cceaff, #ffffff, #ffd6d6, #ffe4b3);
                    filter: blur(100px);
                    z-index: -1;
                }

                html,
                body {
                    overscroll-behavior: none;
                    font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
                }
                .Text_frame {
                    display: grid;
                    margin-top: 2vw;
                }
                .prevent-select,
                .button {
                    -webkit-user-select: none;
                    -ms-user-select: none;
                    user-select: none;
                }

                #t1 {
                    font-weight: bold;
                    font-size: calc(2vw + 3vh);
                    justify-self: center;
                    margin: 0vw;
                }
                #t2 {
                    font-size: calc(0.5vw + 2vh);
                    justify-self: center;
                    margin-top: 0.5vw;
                }

                .joystick-wrapper {
                    display: flex;
                    gap: calc(10vw + 10vh);
                    flex-wrap: wrap;
                    justify-content: center;
                    align-items: center;
                }

                .joystick-container {
                    width: calc(8vw + 4vh);
                    height: calc(8vw + 4vh);
                    background: #737373;
                    background: radial-gradient(
                    circle,
                    rgba(115, 115, 115, 1) 27%,
                    rgba(0, 0, 0, 1) 100%
                    );
                    border-radius: 50%;
                    position: relative;
                    margin: 10px;
                    justify-items: center;
                    align-content: center;
                }

                .joystick {
                    width: calc(4.5vw + 4vh);
                    height: calc(4.5vw + 4vh);
                    background-color: #0c0c0c;
                    border-radius: 50%;
                    transition: transform 0.1s ease;

                    box-shadow: 0px 1px 17px 1px rgba(0, 0, 0, 0.75);
                    -webkit-box-shadow: 0px 1px 17px 1px rgba(0, 0, 0, 0.75);
                    -moz-box-shadow: 0px 1px 17px 1px rgba(0, 0, 0, 0.75);
                }

                .container_left,
                .container_right {
                    border-radius: 100%;
                    background: #737373;
                    background: radial-gradient(
                    circle,
                    rgba(115, 115, 115, 1) 14%,
                    rgba(56, 56, 56, 1) 100%
                    );
                    width: calc(8vw + 10vh);
                    height: calc(8vw + 10vh);
                    justify-items: center;
                    align-content: center;

                    box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -webkit-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                    -moz-box-shadow: 7px 14px 19px 0px rgba(0, 0, 0, 0.47);
                }

                .container_middle {
                    display: flex;
                    gap: 2vw;
                }
                .button {
                    width: calc(4vw + 1vh);
                    height: calc(2vw + 2vh);
                    background-color: #d8d8d8;
                    border-radius: 35%;
                    font-size: calc(1.4vw + 1vh);
                }
                #warning_container {
                    display: none;
                }
                @media (max-width: 700px) {
                    .joystick-wrapper {
                    flex-direction: column;
                    }

                    #main_container {
                    display: none;
                    }
                    #warning_container {
                    display: flex;
                    justify-self: center;
                    align-self: center;
                    margin: 2vw;
                    }
                }
                </style>
            </head>
            <body>
                <div id="main_container">
                <div class="Text_frame">
                    <p class="prevent-select" id="t1">P-Universal Controller</p>
                    <p class="prevent-select" id="t2">v2.0.0</p>
                </div>
                <div class="joystick-wrapper">
                    <div class="container_left">
                    <div class="joystick-container" id="container1">
                        <div class="joystick" id="joystick1"></div>
                    </div>
                    </div>
                    <div class="container_middle">
                    <button
                        class="button"
                        id="box_a"
                        ontouchstart="buttonSendData('a', 1)"
                        ontouchend="buttonSendData('a', 0)"
                        onmousedown="buttonSendData('a', 1)"
                        onmouseup="buttonSendData('a', 0)"
                    >
                        A
                    </button>
                    <button
                        class="button"
                        id="box_b"
                        ontouchstart="buttonSendData('b', 1)"
                        ontouchend="buttonSendData('b', 0)"
                        onmousedown="buttonSendData('b', 1)"
                        onmouseup="buttonSendData('b', 0)"
                    >
                        B
                    </button>
                    <button
                        class="button"
                        id="box_c"
                        ontouchstart="buttonSendData('c', 1)"
                        ontouchend="buttonSendData('c', 0)"
                        onmousedown="buttonSendData('c', 1)"
                        onmouseup="buttonSendData('c', 0)"
                    >
                        C
                    </button>
                    <button
                        class="button"
                        id="box_d"
                        ontouchstart="buttonSendData('d', 1)"
                        ontouchend="buttonSendData('d', 0)"
                        onmousedown="buttonSendData('d', 1)"
                        onmouseup="buttonSendData('d', 0)"
                    >
                        D
                    </button>
                    </div>
                    <div class="container_right">
                    <div class="joystick-container" id="container2">
                        <div class="joystick" id="joystick2"></div>
                    </div>
                    </div>
                </div>
                </div>
                <div id="warning_container">
                <p class="prevent-select" id="t1">
                    Please use landscape mode or a device with a screen width greater than
                    700px!
                </p>
                </div>
                <script>
                class Joystick {
                    constructor(container, knob, id) {
                    this.container = container;
                    this.knob = knob;
                    this.id = id;
                    this.maxDistance = container.clientWidth / 2 - knob.clientWidth / 2;
                    this.activeTouchId = null;
                    this.pos = { x: 0, y: 0 };

                    this.init();
                    }

                    init() {
                    this.container.addEventListener("mousedown", (e) => {
                        this.handleStart(e.clientX, e.clientY);
                    });

                    this.container.addEventListener("touchstart", (e) => {
                        if (this.activeTouchId === null) {
                        const touch = e.changedTouches[0];
                        this.activeTouchId = touch.identifier;
                        this.handleStart(touch.clientX, touch.clientY);
                        }
                    });
                    }

                    handleStart(clientX, clientY) {
                    this.move(clientX, clientY);
                    window.addEventListener("mousemove", this.handleMouseMove);
                    window.addEventListener("mouseup", this.handleEnd);
                    }

                    handleMouseMove = (e) => {
                    this.move(e.clientX, e.clientY);
                    // console.log("test");
                    };

                    handleTouchMove = (e) => {
                    for (let touch of Array.from(e.changedTouches)) {
                        if (touch.identifier === this.activeTouchId) {
                        this.move(touch.clientX, touch.clientY);
                        }
                    }
                    };

                    handleEnd = () => {
                    this.reset();
                    window.removeEventListener("mousemove", this.handleMouseMove);
                    window.removeEventListener("mouseup", this.handleEnd);
                    };

                    move(clientX, clientY) {
                    const rect = this.container.getBoundingClientRect();
                    let x = clientX - rect.left - this.container.clientWidth / 2;
                    let y = clientY - rect.top - this.container.clientHeight / 2;

                    const distance = Math.min(Math.sqrt(x * x + y * y), this.maxDistance);
                    const angle = Math.atan2(y, x);

                    this.pos = {
                        x: Math.cos(angle) * distance,
                        y: Math.sin(angle) * distance,
                    };

                    this.knob.style.transform = `translate(${this.pos.x}px, ${this.pos.y}px)`;
                    }

                    reset() {
                    this.pos = { x: 0, y: 0 };
                    this.activeTouchId = null;
                    this.knob.style.transform = "translate(0px, 0px)";
                    }

                    get normalized() {
                    let x = Math.round((this.pos.x / this.maxDistance) * 128);
                    let y = Math.round((-this.pos.y / this.maxDistance) * 128);

                    x = Math.max(-128, Math.min(127, x));
                    y = Math.max(-128, Math.min(127, y));

                    return { x, y };
                    }
                }

                const joystick1 = new Joystick(
                    document.getElementById("container1"),
                    document.getElementById("joystick1"),
                    1
                );

                const joystick2 = new Joystick(
                    document.getElementById("container2"),
                    document.getElementById("joystick2"),
                    2
                );

                document.addEventListener("touchmove", (e) => {
                    e.preventDefault();
                    for (let touch of Array.from(e.changedTouches)) {
                    [joystick1, joystick2].forEach((joy) => {
                        if (touch.identifier === joy.activeTouchId) {
                        joy.handleTouchMove(e);
                        }
                    });
                    }
                    let x1 = joystick1.normalized.y;
                    let y1 = joystick1.normalized.x;
                    let x2 = joystick2.normalized.y;
                    let y2 = joystick2.normalized.x;

                    var data = x1 + "," + y1 + "," + x2 + "," + y2 + ";";
                    let xhttp1 = new XMLHttpRequest();
                    xhttp1.open("POST", "/joystick", true);
                    xhttp1.setRequestHeader(
                    "Content-Type",
                    "application/x-www-form-urlencoded"
                    );
                    xhttp1.send("value=" + data);

                    // console.log("test");
                });

                document.addEventListener("touchend", (e) => {
                    for (let touch of Array.from(e.changedTouches)) {
                    [joystick1, joystick2].forEach((joy) => {
                        if (touch.identifier === joy.activeTouchId) {
                        joy.handleEnd();
                        }
                    });
                    }
                    var data = 0 + "," + 0 + "," + 0 + "," + 0 + ";";
                    let xhttp1 = new XMLHttpRequest();
                    xhttp1.open("POST", "/joystick", true);
                    xhttp1.setRequestHeader(
                    "Content-Type",
                    "application/x-www-form-urlencoded"
                    );
                    xhttp1.send("value=" + data);
                });

                function buttonSendData(buttonId, state) {
                    var xhttp = new XMLHttpRequest();

                    xhttp.open("POST", "/" + buttonId, true);
                    xhttp.setRequestHeader(
                    "Content-Type",
                    "application/x-www-form-urlencoded"
                    );
                    xhttp.send("state=" + state);
                    console.log("a");
                }

                function updateMaxDistance() {
                    this.maxDistance = this.container.clientWidth / 2 - this.knob.clientWidth / 2;
                }

                window.addEventListener("resize", () => {
                    joystick1.updateMaxDistance();
                    joystick2.updateMaxDistance();
                });
                </script>
            </body>
            </html>
        )rawliteral");
        response->addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
        response->addHeader("Pragma", "no-cache");
        response->addHeader("Expires", "0");
        request->send(response);
    });

    // URL yang sering dipanggil Android/iOS/Windows
    server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    server.on("/gen_204", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    server.on("/hotspot-detect.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    server.on("/ncsi.txt", HTTP_GET, [](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    // Semua permintaan lain tetap arahkan ke halaman utama
    server.onNotFound([](AsyncWebServerRequest *request){
        request->redirect("/");
    });

    // Rute joystick dan tombol (tidak diubah)
    server.on("/joystick", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("value", true)) {
            String data = request->getParam("value", true)->value();
            int idx_1 = data.indexOf(',');
            int idx_2 = data.indexOf(',', idx_1 + 1);
            int idx_3 = data.indexOf(',', idx_2 + 1);
            int idx_4 = data.indexOf(';');

            lx_value = data.substring(0, idx_1).toInt();
            ly_value = data.substring(idx_1 + 1, idx_2).toInt();
            rx_value = data.substring(idx_2 + 1, idx_3).toInt();
            ry_value = data.substring(idx_3 + 1, idx_4).toInt();

            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing value");
        }
    });

    server.on("/a", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
            button_A_state = request->getParam("state", true)->value().toInt();
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing value");
        }
    });

    server.on("/b", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
            button_B_state = request->getParam("state", true)->value().toInt();
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing value");
        }
    });

    server.on("/c", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
            button_C_state = request->getParam("state", true)->value().toInt();
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing value");
        }
    });

    server.on("/d", HTTP_POST, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state", true)) {
            button_D_state = request->getParam("state", true)->value().toInt();
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing value");
        }
    });

    server.begin();
}


void puc::DNS_RUN() {  dnsServer.processNextRequest(); }
bool puc::device_status() {  
    int devices = WiFi.softAPgetStationNum();
    if(devices > 0) {
        return true;
    } else {
        return false;
    }
}
int puc::getLY() { return ly_value; }
int puc::getLX() { return lx_value; }
int puc::getRY() { return ry_value; }
int puc::getRX() { return rx_value; }
int puc::getButtonA() { return button_A_state; }
int puc::getButtonB() { return button_B_state; }
int puc::getButtonC() { return button_C_state; }
int puc::getButtonD() { return button_D_state; }

