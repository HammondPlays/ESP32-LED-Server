#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <httpServer.h>
#include <animationType.h>

class Controller
{
public:
  static void index(AsyncWebServerRequest *request);
  static void config(AsyncWebServerRequest *request);
  static void styles(AsyncWebServerRequest *request);
  static void stylesMobile(AsyncWebServerRequest *request);
  static void mainApp(AsyncWebServerRequest *request);
  static void configApp(AsyncWebServerRequest *request);
  static void ledSwitchOn(AsyncWebServerRequest *request);
  static void ledSwitchOff(AsyncWebServerRequest *request);
  static void ledPower(AsyncWebServerRequest *request);
  static void getBrightness(AsyncWebServerRequest *request);
  static void setBrightness(AsyncWebServerRequest *request, int brightness);
  static void getCurrentAnimation(AsyncWebServerRequest *request);
  static void getAnimationTypes(AsyncWebServerRequest *request);
  static void setAnimationType(AsyncWebServerRequest *request, int animationType);
  static void getLedModes(AsyncWebServerRequest *request);
  static void getLedMode(AsyncWebServerRequest *request);
  static void setLedMode(AsyncWebServerRequest *request, int ledMode);
  static void getSettings(AsyncWebServerRequest *request);
  static void notFound(AsyncWebServerRequest *request);
};

#endif // CONTROLLER_H