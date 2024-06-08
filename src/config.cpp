#include "config.h"

void Config::load() {
    // Config::ledState = true;
    // Config::brightness = 0.5;
    // Config::animationType = AnimationType::FADING;

    // File file = SPIFFS.open("/config.json", "r");

    // if(!file) {
    // Serial.println("Failed to open config file.");
    // Config::save();
    // return;
    // }

    // Serial.println("Config loaded");

    // StaticJsonDocument<1024> doc;
    // deserializeJson(doc, file);	

    // Config::ledState = doc["ledState"] | true;
    // Config::brightness = doc["brightness"] | 0.5;
    // Config::animationType = doc["animationType"] | AnimationType::FADING;

    // file.close();
}

void Config::save() {
    // DynamicJsonDocument doc(1024);
    // doc["ledState"] = Config::ledState;
    // doc["brightness"] = Config::brightness;
    // doc["animationType"] = static_cast<int>(Config::animationType);

    // File file = SPIFFS.open("/config.json", "w");

    // if(!file) {
    //     Serial.println("Failed to open config file for writing.");
    //     return;
    // }

    // serializeJson(doc, file);

    // file.close();
}

void Config::switchLedState() {
    Config::ledState = !Config::ledState;
}