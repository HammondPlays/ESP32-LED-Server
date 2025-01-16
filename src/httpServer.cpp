#include "httpServer.h"
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

void HttpServer::setup()
{
    HttpServer::web.on("/", Controller::index);
    HttpServer::web.on("/led-state", Controller::ledSwitchOnOff);

    HttpServer::web.on(UriRegex("^\\/brightness\\/([0-9]+)$"), HTTP_PUT, []() {
        String brightness = web.pathArg(0);
        Serial.println("Brightness " + brightness);
        Controller::setBrightness(brightness.toInt()); });

    HttpServer::web.on(UriRegex("^\\/animation\\/([0-9]+)$"), HTTP_POST, []() {
        String animation = web.pathArg(0);
        Serial.println("Animation " + animation);
        Controller::setAnimationType(animation.toInt()); });

    HttpServer::web.onNotFound(Controller::notFound);
    HttpServer::web.begin();
}

void HttpServer::loop()
{
    HttpServer::web.handleClient();
}

WebServer HttpServer::web(80);