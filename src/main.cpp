#include <Arduino.h>
#include <animation.h>
#include <shapeAnimation.h>
#include <wifiService.h>
#include <httpServer.h>

#define DELAY 50

Animation animation = Animation(50, DELAY);

void createAnimationObject() {
  switch (Config::ledMode)
    {
        case STRIPE:
            animation = Animation(Config::ledCount, DELAY);
            return;
        case SHAPE:
            animation = ShapeAnimation(Config::ledCount, DELAY, Config::ledCountPerShape);
    }
    animation.setup();
}

void setup()
{
  Serial.begin(9600);
  // Serial.begin(115200);
  SPIFFS.begin();
  Config::load();

  WifiService::setup();
  Serial.println(WiFi.localIP());

  createAnimationObject();

  HttpServer::setup();
}

void loop()
{
  if (Config::resetLEDModeConfig) {
    createAnimationObject();
    Config::resetLEDModeConfig = false;
  }

  animation.loop();
  // Serial.println("Running");
}