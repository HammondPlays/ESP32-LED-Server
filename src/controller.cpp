#include "controller.h"

void Controller::ledSwitchOn(AsyncWebServerRequest* request)
{
    Config::ledState = true;
    Config::save();
    request->send(200, "text/html", Gui::index());
}

void Controller::ledSwitchOff(AsyncWebServerRequest* request)
{
    Config::ledState = false;
    Config::resetCounter = true;
    Config::save();
    request->send(200, "text/html", Gui::index());
}

void Controller::ledPower(AsyncWebServerRequest* request)
{
    String json = "{ \"value\": " + String(Config::ledState ? "true" : "false") + "}";
    request->send(200, "application/json", json);
}

void Controller::getBrightness(AsyncWebServerRequest* request)
{
    Serial.println(Config::brightness);
    String json = "{ \"brightness\": \"" + String(Config::brightness) + "\"}";
    request->send(200, "application/json", json);
}

void Controller::setBrightness(AsyncWebServerRequest* request, int brightness)
{
    Config::brightness = brightness;
    Config::save();
    request->send(200, "text/html", Gui::index());
}

void Controller::getCurrentAnimation(AsyncWebServerRequest* request)
{
    AnimationDetails animationDetails = getAnimationTypeMap()[Config::animationType];
    DynamicJsonDocument doc(1024);

    JsonObject animationObject = doc.createNestedObject(String(static_cast<int>(Config::animationType)));
    animationObject["name"] = animationDetails.name;

    JsonArray parameters = animationObject.createNestedArray("parameters");
    for (const auto& param : animationDetails.animationParameters) {
        parameters.add(param);
    }
    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
}

void Controller::getAnimationTypes(AsyncWebServerRequest* request)
{
    String json = getAnimationTypeJson();
    request->send(200, "application/json", json);
}

void Controller::setAnimationType(AsyncWebServerRequest* request, int animationType)
{
    Serial.printf("Previous animation type: %d\n", Config::animationType);
    Serial.printf("Setting animation type to %d\n", animationType);
    Config::animationType = static_cast<AnimationType>(animationType);
    Config::resetCounter = true;
    Config::save();
    request->send(200, "text/html", Gui::index());
}

void Controller::getLedModes(AsyncWebServerRequest* request)
{
    String json = getLedModeJson();
    request->send(200, "application/json", json);
}

void Controller::getLedMode(AsyncWebServerRequest* request)
{
    LedModeDetails ledModeDetails = getLedModeMap()[Config::ledMode];
    DynamicJsonDocument doc(1024);

    JsonObject ledModeObject = doc.createNestedObject(String(static_cast<int>(Config::ledMode)));
    ledModeObject["name"] = ledModeDetails.name;

    JsonArray parameters = ledModeObject.createNestedArray("parameters");
    for (const auto& param : ledModeDetails.ledModeParameters) {
        parameters.add(param);
    }
    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
}

void Controller::setLedMode(AsyncWebServerRequest* request, int ledMode)
{
    Serial.printf("Previous led mode: %d\n", Config::ledMode);
    Serial.printf("Setting led mode to %d\n", ledMode);
    Config::ledMode = static_cast<LedMode>(ledMode);
    Config::resetCounter = true;
    Config::save();
    request->send(200, "text/html", Gui::index());
}

void Controller::getSettings(AsyncWebServerRequest* request)
{

    DynamicJsonDocument doc(1024);

    JsonObject settingsObject = doc.createNestedObject(String(static_cast<int>(Config::animationType)));
    settingsObject["ledMode"] = Config::ledMode;
    settingsObject["ledCount"] = Config::ledCount;
    settingsObject["ledCountPerHexagon"] = Config::ledCountPerHexagon;

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
}

void Controller::index(AsyncWebServerRequest* request)
{
    request->send(200, "text/html", Gui::index());
}

void Controller::config(AsyncWebServerRequest* request)
{
    request->send(200, "text/html", Gui::config());
}

void Controller::styles(AsyncWebServerRequest* request)
{
    request->send(200, "text/css", Gui::styles());
}

void Controller::stylesMobile(AsyncWebServerRequest* request)
{
    request->send(200, "text/css", Gui::stylesMobile());
}

void Controller::mainApp(AsyncWebServerRequest* request)
{
    request->send(200, "text/plain", Gui::mainApp());
}

void Controller::configApp(AsyncWebServerRequest* request)
{
    request->send(200, "text/plain", Gui::configApp());
}

void Controller::notFound(AsyncWebServerRequest* request)
{
    request->send(404, "text/plain", "Not found");
}