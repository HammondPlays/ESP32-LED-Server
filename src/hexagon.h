#ifndef HEXAGON_H
#define HEXAGON_H

#include <FastLED.h>
#include <colorRGB.h>

class Hexagon {
    public:
    Hexagon(int, int);
    void setRGB(CRGB[], ColorRGB);

    private:
    int hexagonIndex;
    int ledCount;
};

#endif // HEXAGON_H
