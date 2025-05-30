#include <puc_v2.h>

puc myServer;

void setup()
{
    Serial.begin(115200);
    myServer.begin("ESP32_WebServer", "123456789", IPAddress(192, 168, 4, 1));
}

void loop()
{
    // Important function for captive to run
    myServer.DNS_RUN();

    if (myServer.device_status()) {
        int dataLx = myServer.getLX();
        int dataLy = myServer.getLY();
        int dataRx = myServer.getRX();
        int dataRy = myServer.getRY();
        int buttonA = myServer.getButtonA();
        int buttonB = myServer.getButtonB();
        int buttonC = myServer.getButtonC();
        int buttonD = myServer.getButtonD();

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
        Serial.print(" || Button C : ");
        Serial.print(buttonC);
        Serial.print(" || Button D : ");
        Serial.println(buttonD);
    } else {
        Serial.println("There isn't any devices connected!");
    }
}
