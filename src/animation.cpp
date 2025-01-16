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
       
        return ColorRGB(r * Config::brightness,g * Config::brightness,b);
    }

    void Animation::boomerang(){
        leds[this->boomerangLedIndex].setRGB(this->boomerangColor.r, this->boomerangColor.g, this->boomerangColor.b);
        FastLED.show();
        delay(this->delayTime);

        this->boomerangLedIndex += this->boomerangDirection;

        if (this->boomerangLedIndex <= 0 || this->boomerangLedIndex >= this->ledCount)
        {
            this->boomerangDirection *= -1;
            this->boomerangColor = getColor();
        }
        
    }

    void Animation::rainbow(){
        if (this->rainbowColorIndex >= 256)
        {
            this->rainbowColorIndex = 0;
        }
        
        for(uint16_t i=0; i < this->ledCount; i++) {
        ColorRGB color = Wheel(((i * 256 / this->ledCount) + this->rainbowColorIndex) & 255);
        leds[this->ledCount - 1 - i].setRGB(color.r, color.g, color.b);
        }

        FastLED.show();
        delay(this->delayTime);
        
        this->rainbowColorIndex++;
    }

    void Animation::ledSwitchOff(){
        for (int i = 0; i < this->ledCount; i++)
        {
            leds[i].setRGB(0,0,0);
        }
        FastLED.show();
    }

    ColorRGB Animation::Wheel(byte wheelPosition) {
        uint8_t r = 0,
                g = 0, 
                b = 0;
        
        if(wheelPosition < 85) {
        r = wheelPosition * 3;
        g = 255 - wheelPosition * 3;
        b = 0;
        }
        else if(wheelPosition < 170) {
        wheelPosition -= 85;
        r = 255 - wheelPosition * 3;
        g = 0;
        b = wheelPosition * 3;
        }
        else {
        wheelPosition -= 170;
        r = 0;
        g = wheelPosition * 3;
        b = 255 - wheelPosition * 3;
        }

        return ColorRGB(r * Config::brightness, g * Config::brightness, b * Config::brightness);
    }
    