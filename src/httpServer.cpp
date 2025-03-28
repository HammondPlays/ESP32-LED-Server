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

void HttpServer::setup()
{
    HttpServer::web.onRequestBody([](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
        if (request->url() == "/brightness" && request->method() == HTTP_PUT) {
            handleBrightnessPUT(request, data, len, index, total);
        } else {
            Serial.printf("Received body for %s: %u bytes\n", request->url().c_str(), total);
        }
    });


    HttpServer::web.on("/", [](AsyncWebServerRequest* request) {
        Controller::index(request); });
    HttpServer::web.on("/styles.css", [](AsyncWebServerRequest* request) {
        Controller::styles(request); });
    HttpServer::web.on("/app.js", [](AsyncWebServerRequest* request) {
        Controller::app(request); });
    HttpServer::web.on("/led/on", [](AsyncWebServerRequest* request) {
        Controller::ledSwitchOn(request); });
    HttpServer::web.on("/led/off", [](AsyncWebServerRequest* request) {
        Controller::ledSwitchOff(request); });

    HttpServer::web.on("/animations", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getCurrentAnimation(request); });
    HttpServer::web.on("/animation-types", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getAnimationTypes(request); });

    HttpServer::web.on("/brightness", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getBrightness(request); });
    /*HttpServer::web.on("/brightness", HTTP_PUT, [](AsyncWebServerRequest* request) {
        Serial.println("PUT /brightness");

        HttpServer::web.onRequestBody([](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
            Serial.printf("Received body: %u bytes\n", total);

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
        });
    });*/

    HttpServer::web.on("/animations", HTTP_POST, [](AsyncWebServerRequest* request) {
        if (request->hasParam("animations", true)) {
            const AsyncWebParameter* p = request->getParam("animations", true);
            String brightness = p->value();
            Serial.println("Animations " + brightness);
            Controller::setAnimationType(request, brightness.toInt());
        } else {
            request->send(400, "text/plain", "Brightness value missing");
        } 
    });

    HttpServer::web.onNotFound([](AsyncWebServerRequest* request) {
        Controller::notFound(request); });

    HttpServer::web.begin();
}

AsyncWebServer HttpServer::web(80);