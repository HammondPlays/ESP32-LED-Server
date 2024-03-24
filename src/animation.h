#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <hexagonBuilder.h>

class Animation {
    public:
    Animation(Adafruit_NeoPixel, int, int);
    void setup();
    void boomerang();
    byte color;

    private:
    Adafruit_NeoPixel stripe;
    int ledCount;
    int delayTime;

    //Fading
    int staticTime;
    Hexagon hexagons[];

    uint32_t getColor();
    uint8_t isNthBitSet (int n);

};