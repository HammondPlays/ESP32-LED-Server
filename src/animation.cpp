#include "animation.h"

Animation::Animation(int ledCount, int delay)
{
    this->ledCount = ledCount;
    this->delayTime = delay;
    this->color = 1;
}

void Animation::setup()
{
    FastLED.addLeds<NEOPIXEL, LED_PIN>(this->leds, this->ledCount);
}

void Animation::loop()
{
    if (Config::resetCounter)
    {
        resetCounter();
        Config::resetCounter = false;
    }
    
    if (!Config::ledState)
    {
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
        case BREATHING:
            breathing();
            return;
        case STATIC:
            staticColor();
            return;
    }
}

uint8_t Animation::isNthBitSet(int n)
{
    static byte mask[] = {1, 2, 4, 8, 16, 32, 64, 128};
    return ((this->color & mask[n]) != 0) * 255;
}

ColorRGB Animation::getColor()
{
    uint8_t r = isNthBitSet(0),
            g = isNthBitSet(1),
            b = isNthBitSet(2);
    this->color = ((this->color + 1)) % 8;

    return ColorRGB(r, g, b, 100);
}

void Animation::breathing() 
{
    ColorRGB color = ColorRGB(Config::color.r, Config::color.g, Config::color.b, Config::brightness);
    int currentBrightness = 0;
    while (currentBrightness < Config::brightness) {
        if (Config::animationType != BREATHING)
        {
            return;
        }
        
        ColorRGB currentColor = ColorRGB(Config::color.r, Config::color.g, Config::color.b, currentBrightness);
        for (int i = 0; i < this->ledCount; i++)
        {
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b);
        }
        FastLED.show();
        delay(this->delayTime / Config::speed);

        if (currentBrightness >= 50) 
            currentBrightness +=4;
        if (currentBrightness >= 15) 
            currentBrightness +=2;
        else
            currentBrightness++;
    }

    currentBrightness = Config::brightness;
    while(currentBrightness >= 0)
    {
        if (Config::animationType != BREATHING)
        {
            return;
        }

        ColorRGB currentColor = ColorRGB(Config::color.r, Config::color.g, Config::color.b, currentBrightness);
        for (int i = 0; i < this->ledCount; i++)
        {
            leds[i].setRGB(currentColor.r, currentColor.g, currentColor.b);
        }
        FastLED.show();
        delay(this->delayTime / Config::speed);

        if (currentBrightness > 50) 
            currentBrightness -=4;
        if (currentBrightness > 15) 
            currentBrightness -=2;
        else
            currentBrightness--;
    }

    delay(this->delayTime * 10);
}

void Animation::staticColor() 
{
    ColorRGB color = ColorRGB(Config::color.r, Config::color.g, Config::color.b, Config::brightness);
    for (int i = 0; i < this->ledCount; i++)
    {
        leds[i].setRGB(color.r, color.g, color.b);
    }
    FastLED.show();
}

void Animation::boomerang()
{
    ColorRGB color = getColor();
    for (int boomerangPosition = 0; boomerangPosition < this->ledCount; boomerangPosition++)
    {
        if (Config::animationType != BOOMERANG)
        {
            return;
        }

        ColorRGB colorWithBrightness = ColorRGB(color.r, color.g, color.b, Config::brightness);

        for (int i = 0; i < boomerangPosition; i++)
        {   
            leds[i].setRGB(colorWithBrightness.r, colorWithBrightness.g, colorWithBrightness.b);
        }    
        FastLED.show();
        delay(this->delayTime / Config::speed);
    }

    color = getColor();
    
    for (int boomerangPosition = this->ledCount; boomerangPosition >= 0; boomerangPosition--)
    {
        if (Config::animationType != BOOMERANG)
        {
            return;
        }

        ColorRGB colorWithBrightness = ColorRGB(color.r, color.g, color.b, Config::brightness);

        for (int i = this->ledCount; i > boomerangPosition; i--)
        {   
            leds[i].setRGB(colorWithBrightness.r, colorWithBrightness.g, colorWithBrightness.b);
        }    
        FastLED.show();
        delay(this->delayTime / Config::speed);
    }
}

void Animation::rainbow()
{
    if (this->rainbowColorIndex >= 256)
    {
        this->rainbowColorIndex = 0;
    }

    for (uint16_t i = 0; i < this->ledCount; i++)
    {
        ColorRGB color = Wheel(((i * 256 / this->ledCount) + this->rainbowColorIndex) & 255);
        leds[this->ledCount - 1 - i].setRGB(color.r, color.g, color.b);
    }

    FastLED.show();
    delay(this->delayTime);

    this->rainbowColorIndex++;
}

void Animation::ledSwitchOff()
{
    for (int i = 0; i < this->ledCount; i++)
    {
        leds[i].setRGB(0, 0, 0);
    }
    FastLED.show();
}

void Animation::resetCounter()
{
    this->rainbowColorIndex = 0;
}

ColorRGB Animation::Wheel(byte wheelPosition)
{
    uint8_t r = 0,
            g = 0,
            b = 0;

    if (wheelPosition < 85)
    {
        r = wheelPosition * 3;
        g = 255 - wheelPosition * 3;
        b = 0;
    }
    else if (wheelPosition < 170)
    {
        wheelPosition -= 85;
        r = 255 - wheelPosition * 3;
        g = 0;
        b = wheelPosition * 3;
    }
    else
    {
        wheelPosition -= 170;
        r = 0;
        g = wheelPosition * 3;
        b = 255 - wheelPosition * 3;
    }

    return ColorRGB(r, g, b, Config::brightness);
}
