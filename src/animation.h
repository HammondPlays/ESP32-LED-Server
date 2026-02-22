#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include <FastLED.h>
#include <config.h>
#include <animationType.h>
#include <colorRGB.h>

#define LED_PIN 32
#define LED_COUNT 500

class Animation
{
public:
    Animation(int, int);
    void setup();
    void loop();
    void ledSwitchOff();
    void resetCounter();
    virtual void boomerang();
    virtual void rainbow();
    void breathing();
    void staticColor();
    byte color;

protected:
    int ledCount;
    int delayTime;
    CRGB leds[LED_COUNT];

    // Rainbow
    int rainbowColorIndex;
    ColorRGB Wheel(byte wheelPosition);
  
    ColorRGB getColor();
    uint8_t isNthBitSet(int n);
};

#endif
