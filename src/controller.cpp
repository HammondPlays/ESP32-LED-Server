#include "httpServer.h"

void Controller::index() {
    HttpServer::web.send(200, "text/html", Gui::index());
}

void Controller::notFound() {
  HttpServer::web.send(404, "text/plain", "Not found");
}