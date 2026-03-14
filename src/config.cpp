#include "config.h"

void Config::load() {
    File file = SPIFFS.open("/config.json", "r");

    if(!file) {
    Serial.println("Failed to open config file.");
    Config::save();
    return;
    }

    Serial.println("Config loaded");

    StaticJsonDocument<1024> doc;
    deserializeJson(doc, file);	

    Config::ledState = doc["ledState"] | true;
    Config::brightness = doc["brightness"] | 0.25;
    Config::animationType = doc["animationType"] | AnimationType::RAINBOW;
    Config::ledMode = doc["ledMode"] | LedMode::STRIPE;
    Config::ledCount = doc["ledCount"] | 50;
    Config::ledCountPerShape = doc["ledCountPerShape"] | 6;

    file.close();
}

void Config::save() {
    DynamicJsonDocument doc(1024);
    doc["ledState"] = Config::ledState;
    doc["brightness"] = Config::brightness;
    doc["animationType"] = static_cast<int>(Config::animationType);
    doc["ledMode"] = static_cast<int>(Config::ledMode);
    doc["ledCount"] = Config::ledCount;
    doc["ledCountPerShape"] = Config::ledCountPerShape;

    File file = SPIFFS.open("/config.json", "w");

    if(!file) {
        Serial.println("Failed to open config file for writing.");
        return;
    }

    serializeJson(doc, file);

    file.close();
}