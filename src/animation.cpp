#include "animation.h"

    Animation::Animation(Adafruit_NeoPixel neoPixel, int ledCount, int delay) {
        this->stripe = neoPixel;
        this->ledCount = ledCount;
        this->delayTime = delay;
        this->color = 1;

        
    }

    void Animation::setup(){
        this->stripe.begin();
    }

    uint8_t Animation::isNthBitSet (int n) {
    static byte mask[] = {1, 2, 4, 8, 16, 32, 64, 128};
    return ((this->color & mask[n]) != 0) * 255;

    }

    uint32_t Animation::getColor() {
        uint8_t r = isNthBitSet(0), 
                g = isNthBitSet(1),     
                b = isNthBitSet(2);
        this->color = ((this->color + 1) ) % 8;
        return this->stripe.Color(r,g,b);
    }

    void Animation::boomerang(){
        uint32_t currentColor = getColor();
        for (int i = 0; i < this->ledCount; i++)
        {
            stripe.setPixelColor(i, currentColor);
            stripe.show();
            delay(this->delayTime);
        }
        currentColor = getColor(); 
        for (int i = this->ledCount-1; i >= 0; i--)
        {
            stripe.setPixelColor(i, currentColor);
            stripe.show();
            delay(this->delayTime);
        }
    }

    