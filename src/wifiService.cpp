#include "wifiService.h"

void WifiService::setup(){
    WiFiManager wifiManager;
    wifiManager.autoConnect("ESP32", "password");
}

void WifiService::reset() {
  WiFi.disconnect(true);
}
