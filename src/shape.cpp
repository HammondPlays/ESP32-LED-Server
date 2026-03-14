#include "shape.h"

Shapes::Shapes(int hexagonIndex, int ledCount) {
    this->hexagonIndex = hexagonIndex;
    this->ledCount = ledCount;
}

void Shapes::setRGB(CRGB* pixels, ColorRGB color) {
    for (int i = this->hexagonIndex * ledCount; i < this->hexagonIndex * (ledCount + 1); i++)
    {
        pixels[i].setRGB(color.r, color.g, color.b);
    }
    FastLED.show();
}