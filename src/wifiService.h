#include <WiFiManager.h>
#include <WiFi.h>
#include <string.h>

class WifiService
{
private:
    /* data */
public:
    static void setup();
    static void reset();
};

void WifiService::setup(){
    WiFiManager wifiManager;
    wifiManager.autoConnect("ESP32", "password");
}

void WifiService::reset() {
  WiFi.disconnect(true);
}
