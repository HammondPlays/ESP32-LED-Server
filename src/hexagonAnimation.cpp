#include "hexagonAnimation.h"

    HexagonAnimation::HexagonAnimation(int ledcount, int delay, int ledPerHexagon)
    : Animation(ledcount, delay)
    {
        int hexagonCount = ledcount / ledPerHexagon;
        for (int i = 0; i < hexagonCount; i++) {
            hexagons.push_back(Hexagon(0, ledPerHexagon));
        }
    }

void HexagonAnimation::boomerang()
{
    ColorRGB color = getColor();
    for (int boomerangPosition = 0; boomerangPosition < this->hexagons.size(); boomerangPosition++)
    {
        if (Config::animationType != BOOMERANG)
        {
            return;
        }

        ColorRGB colorWithBrightness = ColorRGB(color.r, color.g, color.b, Config::brightness);

        for (int i = 0; i < boomerangPosition; i++)
        {   
            this->hexagons[i].setRGB(this->leds, colorWithBrightness);
        }    
        FastLED.show();
        delay(this->delayTime / Config::speed);
    }

    color = getColor();
    
    for (int boomerangPosition = this->hexagons.size(); boomerangPosition >= 0; boomerangPosition--)
    {
        if (Config::animationType != BOOMERANG)
        {
            return;
        }

        ColorRGB colorWithBrightness = ColorRGB(color.r, color.g, color.b, Config::brightness);

        for (int i = this->ledCount; i > boomerangPosition; i--)
        {   
            this->hexagons[i].setRGB(leds, colorWithBrightness);
        }    
        FastLED.show();
        delay(this->delayTime / Config::speed);
    }
}

void HexagonAnimation::rainbow()
{
    if (this->rainbowColorIndex >= 256)
    {
        this->rainbowColorIndex = 0;
    }

    for (uint16_t i = 0; i < this->hexagons.size(); i++)
    {
        ColorRGB color = Wheel(((i * 256 / this->ledCount) + this->rainbowColorIndex) & 255);
        this->hexagons[this->hexagons.size() - 1 - i].setRGB(leds, color);
    }

    FastLED.show();
    delay(this->delayTime);

    this->rainbowColorIndex++;
}