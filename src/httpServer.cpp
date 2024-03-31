#include "httpServer.h"
    
void HttpServer::setup() {
    HttpServer::ip = WiFi.localIP().toString();
    
    HttpServer::web.on("/", Controller::index);
	HttpServer::web.onNotFound(Controller::notFound);
    HttpServer::web.begin();
}
  
void HttpServer::loop() {
    HttpServer::web.handleClient();
}

WebServer HttpServer::web(80);
String HttpServer::ip;