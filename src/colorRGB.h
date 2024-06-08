#include <Arduino.h>

#ifndef COLORRGB_H
#define COLORRGB_H

class ColorRGB {
    public:
    uint8_t r,g,b;
    ColorRGB(uint8_t r, uint8_t g, uint8_t b);
};

#endif // COLORRGB_H