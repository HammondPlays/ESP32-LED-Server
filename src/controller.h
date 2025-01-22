#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <httpServer.h>
#include <animationType.h>

class Controller
{
public:
  static void index();
  static void styles();
  static void app();
  static void ledSwitchOnOff();
  static void getBrightness();
  static void setBrightness(int brightness);
  static void getAnimationTypes();
  static void setAnimationType(int animationType);
  static void notFound();
  static String SendHTML(uint8_t led1stat, uint8_t led2stat);
};

#endif // CONTROLLER_H