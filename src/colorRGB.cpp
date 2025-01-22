#include "colorRGB.h"

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b, double brightness)
{
    brightness = brightness / 100.0;
    this->r = uint8_t(r * brightness);
    this->g = uint8_t(g * brightness);
    this->b = uint8_t(b * brightness);
}