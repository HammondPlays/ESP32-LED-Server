#ifndef CONFIG_H
#define CONFIG_H

#include <FS.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <animationType.h>
#include <animation.h>
#include <ledMode.h>
#include <colorRGB.h>

class Config
{
public:
  inline static int ledCount = 50;
  inline static int ledCountPerHexagon = 6;
  inline static LedMode ledMode = LedMode::STRIPE;
  inline static bool ledState = true;
  inline static int brightness = 25;
  inline static AnimationType animationType = AnimationType::RAINBOW;
  inline static float speed = 1.0;
  inline static ColorRGB color = ColorRGB(255, 0, 0, 100);
  inline static bool resetCounter = false;
  inline static bool resetLEDModeConfig = false;

  static void save();
  static void load();
};

#endif