#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include <FastLED.h>
#include <hexagonBuilder.h>
#include <config.h>
#include <animationType.h>
#include <colorRGB.h>

#define LED_PIN 32
#define LED_COUNT 100

class Animation
{
public:
    Animation(int, int);
    void setup();
    void loop();
    void ledSwitchOff();
    void boomerang();
    void rainbow();
    byte color;

private:
    int ledCount;
    int delayTime;
    CRGB leds[LED_COUNT];

    // Rainbow
    int rainbowColorIndex;
    ColorRGB Wheel(byte wheelPosition);

    // Boomerang
    int boomerangLedIndex;
    int8_t boomerangDirection = 1; //Positive forward, Negative backwards
    ColorRGB boomerangColor = ColorRGB(0,0,0,1.0);
    
    // Fading
    int staticTime;
    Hexagon hexagons[];


    ColorRGB getColor();
    uint8_t isNthBitSet(int n);
};

#endif
