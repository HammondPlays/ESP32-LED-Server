#ifndef LEDMODE_H
#define LEDMODE_H

#include <string>
#include <map>
#include <vector>
#include "ArduinoJson.h"

enum LedMode {
    STRIPE,
    SHAPE
};

struct LedModeDetails {
    std::string name;
    std::vector<std::string> ledModeParameters; // List of parameters
};

std::map<LedMode, LedModeDetails> getLedModeMap();

String getLedModeJson();

#endif