#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

#include <string>
#include <map>
#include "ArduinoJson.h"
#include <vector>

enum AnimationType {
    BOOMERANG,
    RAINBOW,
    STATIC
};

struct AnimationDetails {
    std::string name;
    std::vector<std::string> animationParameters; // List of parameters
};

std::map<AnimationType, AnimationDetails> getAnimationTypeMap();

String getAnimationTypeJson();

#endif