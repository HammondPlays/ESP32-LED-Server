#include "controller.h"

void Controller::ledSwitchOnOff(AsyncWebServerRequest* request)
{
    Config::switchLedState();
    Config::resetCounter = true;
    Config::save();
    request->send(200, "text/html", Gui::index());
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
    String json = "{ \"animation\": \"" + String(static_cast<int>(Config::animationType)) + "\"}";
    request->send(200, "application/json", json);
}

void Controller::getAnimationTypes(AsyncWebServerRequest* request)
{
    String json = getAnimationTypeJson();
    request->send(200, "application/json", json);
}

void Controller::setAnimationType(AsyncWebServerRequest* request, int animationType)
{
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