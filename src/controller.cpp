#include "httpServer.h"

void Controller::index() {
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::ledSwitchOnOff() {
    Config::switchLedState();
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
} 

void Controller::setBrightness(double brightness) {
    Config::brightness = brightness;
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::notFound() {
  HttpServer::web.send(404, "text/plain", "Not found");
}

void Controller::setAnimationType(int animationType) {
    Config::animationType = static_cast<AnimationType>(animationType);
    Config::save();
    HttpServer::web.send(200, "text/html", Gui::index());
}