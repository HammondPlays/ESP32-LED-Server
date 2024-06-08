#ifndef WORDCLOCK_SERVER_H
#define WORDCLOCK_SERVER_H

#include <Arduino.h>
#include <WebServer.h>
#include <controller.h>
#include <gui.h>
#include <Animation.h>
#include <config.h>

class HttpServer {
  public:
    static WebServer web;
    
    static void setup();
    static void loop();
};

#endif