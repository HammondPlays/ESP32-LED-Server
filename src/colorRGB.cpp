#include "colorRGB.h"

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b, double brightness)
{
    brightness = brightness / 100.0;
    this->r = uint8_t(r * brightness);
    this->g = uint8_t(g * brightness);
    this->b = uint8_t(b * brightness);
}

std::string ColorRGB::toHex() {
    char hexColor[8];
    snprintf(hexColor, sizeof(hexColor), "#%02X%02X%02X", this->r, this->g, this->b);
    return std::string(hexColor);
}

ColorRGB ColorRGB::hexToRGB(const std::string& hexColor) {
    // Ensure the hex color starts with '#'
    if (hexColor[0] != '#' || hexColor.length() != 7) {
        return ColorRGB(0,0,0,100); // Return black as a fallback
    }

    // Convert the hex values to integers
    int r = std::stoi(hexColor.substr(1, 2), nullptr, 16); // Red
    int g = std::stoi(hexColor.substr(3, 2), nullptr, 16); // Green
    int b = std::stoi(hexColor.substr(5, 2), nullptr, 16); // Blue

    return ColorRGB(r, g, b, 100);
}