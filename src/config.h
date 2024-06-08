#ifndef CONFIG_H
#define CONFIG_H
#include <FS.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <animationType.h>
#include <animation.h>


class Config {
  public:
    inline static bool ledState = true;
    inline static double brightness = 0.5;
    inline static AnimationType animationType = AnimationType::FADING;

    static void switchLedState();
    static void save();
    static void load();
};

#endif