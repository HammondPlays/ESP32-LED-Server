#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <Arduino.h>
#include <AsyncEventSource.h>
#include <controller.h>
#include <gui.h>
#include <Animation.h>
#include <config.h>
#include "colorRGB.h"

class HttpServer
{
public:
  static AsyncWebServer web;

  static void setup();
};

#endif