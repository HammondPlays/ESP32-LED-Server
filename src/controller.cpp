#include "controller.h"

void Controller::ledSwitchOnOff()
{
    Config::switchLedState();
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::setBrightness(int brightness)
{
    Config::brightness = brightness / 100.0;
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::getAnimationTypes()
{
    String json = getAnimationTypeJson();
    HttpServer::web.send(200, "application/json", json);
}

void Controller::setAnimationType(int animationType)
{
    Config::animationType = static_cast<AnimationType>(animationType);
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::index()
{
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::notFound()
{
    HttpServer::web.send(404, "text/plain", "Not found");
}