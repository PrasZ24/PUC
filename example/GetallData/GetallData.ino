#include <puc.h>

puc myServer;

void setup() {
    Serial.begin(115200);
    myServer.begin("ESP32_WebServer", "123456789", IPAddress(192, 168, 4, 1), false);
}

void loop() {
    int dataLx = myServer.getLX();
    int dataLy = myServer.getLY();
    int dataRx = myServer.getRX();
    int dataRy = myServer.getRY();
    int buttonA = myServer.getButtonA();
    int buttonB = myServer.getButtonB();
    int button1 = myServer.getButton1();
    int button2 = myServer.getButton2();
    int button3 = myServer.getButton3();
    int button4 = myServer.getButton4();
    int button5 = myServer.getButton5();
    int button6 = myServer.getButton6();

    Serial.print("Analog Left X  : ");
    Serial.print(dataLx);
    Serial.print(" || Analog Left Y  : ");
    Serial.print(dataLy);
    Serial.print(" || Analog Right X : ");
    Serial.print(dataRx);
    Serial.print(" || Analog Right Y : ");
    Serial.print(dataRy);

    Serial.print(" || Button A : ");
    Serial.print(buttonA);
    Serial.print(" || Button B : ");
    Serial.print(buttonB);
    Serial.print(" || Button 1 : ");
    Serial.print(button1);
    Serial.print(" || Button 2 : ");
    Serial.print(button2);
    Serial.print(" || Button 3 : ");
    Serial.print(button3);
    Serial.print(" || Button 4 : ");
    Serial.print(button4);
    Serial.print(" || Button 5 : ");
    Serial.print(button5);
    Serial.print(" || Button 6 : ");
    Serial.println(button6);
}
