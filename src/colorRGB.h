#ifndef COLORRGB_H
#define COLORRGB_H

#include <Arduino.h>

class ColorRGB {
public:
    uint8_t r, g, b;
    ColorRGB(uint8_t r, uint8_t g, uint8_t b, double brightness);
};

#endif // COLORRGB_H