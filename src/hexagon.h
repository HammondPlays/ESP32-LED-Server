#include <Adafruit_NeoPixel.h>

class Hexagon {
    public:
    Hexagon();
    Hexagon(int, int);
    void display(Adafruit_NeoPixel, uint32_t);

    private:
    int hexagonIndex;
    int ledCount;
};