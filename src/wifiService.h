#ifndef WIFISERVICE_H
#define WIFISERVICE_H

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

#endif // WIFISERVICE_H