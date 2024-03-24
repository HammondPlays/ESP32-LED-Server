#include "hexagon.h"

Hexagon::Hexagon() {

}

//LedCount = Number of leds in each Hexagon
//HexagonIndex = Index of Hexagon
Hexagon::Hexagon(int hexagonIndex, int ledCount) {
    this->hexagonIndex = hexagonIndex;
    this->ledCount = ledCount;
}

void Hexagon::display(Adafruit_NeoPixel pixels, uint32_t color) {
    for (int i = this->hexagonIndex * ledCount; i < this->hexagonIndex * (ledCount + 1); i++)
    {
        pixels.setPixelColor(i, color);
    }
    pixels.show();
}