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

void Controller::index(AsyncWebServerRequest* request)
{
    request->send(200, "text/html", Gui::index());
}

void Controller::styles(AsyncWebServerRequest* request)
{
    request->send(200, "text/css", Gui::styles());
}

void Controller::app(AsyncWebServerRequest* request)
{
    request->send(200, "text/plain", Gui::app());
}

void Controller::notFound(AsyncWebServerRequest* request)
{
    request->send(404, "text/plain", "Not found");
}