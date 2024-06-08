#include "animation.h"

    Animation::Animation(int ledCount, int delay) {
        this->ledCount = ledCount;
        this->delayTime = delay;
        this->color = 1;
    }

    void Animation::setup(){
        FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, this->ledCount);
    }

    void Animation::loop(){
        if (!Config::ledState) {
            ledSwitchOff();
            return;
        }
        
        switch (Config::animationType)
        {
        case FADING:
            fading();
            return;
        case BOOMERANG:
            boomerang();
            return;
        case RAINBOW:
            rainbow();
            return;
        }
    }

    uint8_t Animation::isNthBitSet (int n) {
    static byte mask[] = {1, 2, 4, 8, 16, 32, 64, 128};
    return ((this->color & mask[n]) != 0) * 255;

    }

    ColorRGB Animation::getColor() {
        uint8_t r = isNthBitSet(0), 
                g = isNthBitSet(1),     
                b = isNthBitSet(2);
        this->color = ((this->color + 1) ) % 8;
       
        return ColorRGB(r,g,b);
    }

    void Animation::fading(){
        for (int i = 0; i < this->ledCount; i++)
        {
            ColorRGB currentColor = getColor();
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b); 
            
            delay(this->delayTime);
        }
        FastLED.show();
    }

    void Animation::boomerang(){
        ColorRGB currentColor = getColor();
        for (int i = 0; i < this->ledCount; i++)
        {
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b);
            FastLED.show();
            delay(this->delayTime);
        }
        currentColor = getColor(); 
        for (int i = this->ledCount-1; i >= 0; i--)
        {
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b);
            FastLED.show();
            delay(this->delayTime);
        }
    }

    //TODO: rainbow color animation
    void Animation::rainbow(){
        for (int i = 0; i < this->ledCount; i++)
        {
            ColorRGB currentColor = getColor();
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b);
            FastLED.show();
            delay(this->delayTime);
        }
    }

    void Animation::ledSwitchOff(){
        for (int i = 0; i < this->ledCount; i++)
        {
            leds[i].setRGB(0,0,0);
            FastLED.show();
        }
    }

    