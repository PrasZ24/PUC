#include <puc.h>

puc myServer;

void setup() {
    Serial.begin(115200);
    myServer.begin("ESP32_WebServer", "123456789", IPAddress(192, 168, 4, 1), false);
}

void loop() {
    int dataLx = myServer.getLX();
    Serial.print("Analog Left X : ");
    Serial.print(dataLx);
    Serial.print(" || Analog Left X : ");
    Serial.print(dataLx);
    
}
