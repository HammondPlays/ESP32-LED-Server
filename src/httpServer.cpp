#include "httpServer.h"
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

void handleBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
  if(!index){
    Serial.printf("BodyStart: %u B\n", total);
  }
  for(size_t i=0; i<len; i++){
    Serial.write(data[i]);
  }
  if(index + len == total){
    Serial.printf("BodyEnd: %u B\n", total);
  }
}

void HttpServer::setup()
{
    HttpServer::web.on("/", [](AsyncWebServerRequest* request) {
        Controller::index(request); });
    HttpServer::web.on("/styles.css", [](AsyncWebServerRequest* request) {
        Controller::styles(request); });
    HttpServer::web.on("/app.js", [](AsyncWebServerRequest* request) {
        Controller::app(request); });
    HttpServer::web.on("/led-state", [](AsyncWebServerRequest* request) {
        Controller::ledSwitchOnOff(request); });

    HttpServer::web.on("/animations", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getCurrentAnimation(request); });
    HttpServer::web.on("/animation-types", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getAnimationTypes(request); });

    HttpServer::web.on("/brightness", HTTP_GET, [](AsyncWebServerRequest* request) {
        Controller::getBrightness(request); });
    HttpServer::web.on("/brightness", HTTP_PUT, [](AsyncWebServerRequest* request) {
        Serial.println("PUT /brightness");
        handleBody(request, request->_tempObject, request->getArg(0)->length(), 0, request->getArg(0)->length());
        if (request->hasParam("brightness", true)) {
            const AsyncWebParameter* p = request->getParam("brightness", true);
            String brightness = p->value();
            Serial.println("Brightness " + brightness);
            Controller::setBrightness(request, brightness.toInt());
        } else {
            request->send(400, "text/plain", "Brightness value missing");
        } 
        }
    );

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