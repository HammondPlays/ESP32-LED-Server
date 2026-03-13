#include "httpServer.h"
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

void handleBrightnessPUT(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total){
    Serial.printf("Received body for /brightness: %u bytes\n", total);

    // Allocate a JSON document (adjust size as needed)
    StaticJsonDocument<200> jsonDoc;

    // Parse the JSON body
    DeserializationError error = deserializeJson(jsonDoc, data, len);
    if (error) {
        Serial.println("Failed to parse JSON");
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // Extract the "brightness" value from the JSON
    if (jsonDoc.containsKey("brightness")) {
        int brightness = jsonDoc["brightness"];
        Serial.printf("Brightness: %d\n", brightness);

        // Call your controller to set the brightness
        Controller::setBrightness(request, brightness);

        // Send a success response
        request->send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("Brightness key missing in JSON");
        request->send(400, "application/json", "{\"error\":\"Missing 'brightness' key\"}");
    }
}

void handleAnimationPUT(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total){
    Serial.printf("Received body for /animations: %u bytes\n", total);

    // Allocate a JSON document (adjust size as needed)
    StaticJsonDocument<200> jsonDoc;

    // Parse the JSON body
    DeserializationError error = deserializeJson(jsonDoc, data, len);
    if (error) {
        Serial.println("Failed to parse JSON");
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // Extract the "brightness" value from the JSON
    if (jsonDoc.containsKey("animation")) {
        AnimationType animation = jsonDoc["animation"];
        Serial.printf("Animation: %d\n", animation);

        float speed = jsonDoc["speed"];
        ColorRGB color = ColorRGB::hexToRGB(jsonDoc["color"] | "#ff0000");

        Serial.printf("Color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b);
        Serial.printf("Speed: %.2f\n", speed);

        Config::speed = speed;
        Config::color = color;

        // Call your controller to set the brightness
        Controller::setAnimationType(request, animation);
        request->send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("Animation key missing in JSON");
        request->send(400, "application/json", "{\"error\":\"Missing 'animation' key\"}");
    }
}

void handleLedModePUT(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total){
    Serial.printf("Received body for /led-mode: %u bytes\n", total);

    // Allocate a JSON document (adjust size as needed)
    StaticJsonDocument<200> jsonDoc;

    // Parse the JSON body
    DeserializationError error = deserializeJson(jsonDoc, data, len);
    if (error) {
        Serial.println("Failed to parse JSON");
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // Extract the "brightness" value from the JSON
    if (jsonDoc.containsKey("ledMode")) {
        LedMode ledMode = jsonDoc["ledMode"];
        Serial.printf("LedMode: %d\n", ledMode);

        bool resetLEDModeConfig = ledMode != Config::ledMode;

        if (jsonDoc.containsKey("ledCount")) {
            int ledCount = jsonDoc["ledCount"];
            Serial.printf("LedCount: %d\n", ledCount);
            Config::ledCount = ledCount;
            resetLEDModeConfig = true;
        }

        if (jsonDoc.containsKey("ledCountPerHexagon")) {
            int ledCountPerHexagon = jsonDoc["ledCountPerHexagon"];
            Serial.printf("LedCountPerHexagon: %d\n", ledCountPerHexagon);
            Config::ledCountPerHexagon = ledCountPerHexagon;
            resetLEDModeConfig = true;
        }

        if (resetLEDModeConfig) {
            Config::ledMode = ledMode;
            Config::resetLEDModeConfig = true;
        }

        request->send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("LedMode key missing in JSON");
        request->send(400, "application/json", "{\"error\":\"Missing 'ledMode' key\"}");
    }
}

void handleSettingsPUT(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total){
    Serial.printf("Received body for /animations: %u bytes\n", total);

    // Allocate a JSON document (adjust size as needed)
    StaticJsonDocument<200> jsonDoc;

    // Parse the JSON body
    DeserializationError error = deserializeJson(jsonDoc, data, len);
    if (error) {
        Serial.println("Failed to parse JSON");
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // Extract the "brightness" value from the JSON
    if (jsonDoc.containsKey("ledMode")) {
        LedMode ledMode = jsonDoc["ledMode"];
        Serial.printf("LedMode: %d\n", ledMode);

        bool resetLEDModeConfig = ledMode != Config::ledMode;

        if (jsonDoc.containsKey("ledCount")) {
            int ledCount = jsonDoc["ledCount"];
            Serial.printf("LedCount: %d\n", ledCount);
            Config::ledCount = ledCount;
            resetLEDModeConfig = true;
        }

        if (jsonDoc.containsKey("ledCountPerHexagon")) {
            int ledCountPerHexagon = jsonDoc["ledCountPerHexagon"];
            Serial.printf("LedCountPerHexagon: %d\n", ledCountPerHexagon);
            Config::ledCountPerHexagon = ledCountPerHexagon;
            resetLEDModeConfig = true;
        }

        if (resetLEDModeConfig) {
            Config::ledMode = ledMode;
            Config::resetLEDModeConfig = true;
        }

        request->send(200, "application/json", "{\"status\":\"success\"}");
    } else {
        Serial.println("LedMode key missing in JSON");
        request->send(400, "application/json", "{\"error\":\"Missing 'animation' key\"}");
    }
}


void handleLEDPowerPUT(AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total){
    Serial.printf("Received body for /animations: %u bytes\n", total);

        // Allocate a JSON document (adjust size as needed)
    StaticJsonDocument<200> jsonDoc;

    // Parse the JSON body
    DeserializationError error = deserializeJson(jsonDoc, data, len);
    if (error) {
        Serial.println("Failed to parse JSON");
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
    }

    // Extract the "brightness" value from the JSON
    if (jsonDoc.containsKey("value")) {
        boolean power = jsonDoc["value"];
        Serial.printf("Power: %s\n", power ? "true" : "false");
        
        if (power) {
            Controller::ledSwitchOn(request);
        } else {
            Controller::ledSwitchOff(request);
        }
        request->send(200, "application/json", "{\"status\":\"success\"}");        
    } else {
        Serial.println("LED Power value missing in JSON");
        request->send(400, "application/json", "{\"error\":\"Missing 'animation' key\"}");
    }
}


void HttpServer::setup()
{
    HttpServer::web.on("/main/app.js", [](AsyncWebServerRequest* request) {
        Controller::mainApp(request); });
    HttpServer::web.on("/", [](AsyncWebServerRequest* request) {
        Controller::index(request); });
    HttpServer::web.on("/config/app.js", [](AsyncWebServerRequest* request) {
        Serial.println("Received request for /config/app.js");
        Controller::configApp(request); });
    HttpServer::web.on("/config", [](AsyncWebServerRequest* request) {
        Serial.println("Received request for /config");
        Controller::config(request); });
    HttpServer::web.on("/styles-desktop.css", [](AsyncWebServerRequest* request) {
        Controller::styles(request); });
    HttpServer::web.on("/styles-mobile.css", [](AsyncWebServerRequest* request) {
        Controller::stylesMobile(request); });
    HttpServer::web.on("/led", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::ledPower(request); 
    });
    HttpServer::web.on("/led", HTTP_PUT, [](AsyncWebServerRequest* request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        handleLEDPowerPUT(request, data, len, index, total);
    });

    HttpServer::web.on("/animations", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getCurrentAnimation(request); 
    });
    HttpServer::web.on("/animations", HTTP_PUT, [](AsyncWebServerRequest* request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        handleAnimationPUT(request, data, len, index, total);
    });

    HttpServer::web.on("/animation-types", HTTP_GET, [](AsyncWebServerRequest* request) {
    Controller::getAnimationTypes(request); });

    HttpServer::web.on("/brightness", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getBrightness(request); 
    });
    HttpServer::web.on("/brightness", HTTP_PUT, [](AsyncWebServerRequest* request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        handleBrightnessPUT(request, data, len, index, total);
    });

    HttpServer::web.on("/settings", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getSettings(request);
    });
    HttpServer::web.on("/settings", HTTP_PUT, [](AsyncWebServerRequest* request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        handleSettingsPUT(request, data, len, index, total);
    });

    HttpServer::web.on("/led-mode", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getLedMode(request); 
    });
    HttpServer::web.on("/led-mode", HTTP_PUT, [](AsyncWebServerRequest* request){}, NULL, [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        handleLedModePUT(request, data, len, index, total);
    });
    HttpServer::web.on("/led-modes", HTTP_GET, [](AsyncWebServerRequest* request) {
    Controller::getLedModes(request); });

    HttpServer::web.onNotFound([](AsyncWebServerRequest* request) {
        Controller::notFound(request); });

    HttpServer::web.begin();
}

AsyncWebServer HttpServer::web(80);