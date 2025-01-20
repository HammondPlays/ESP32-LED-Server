#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

#include <string>
#include <map>
#include "ArduinoJson.h"

enum AnimationType {
    BOOMERANG,
    RAINBOW
};

std::map<AnimationType, std::string> getAnimationTypeMap();

String getAnimationTypeJson();

#endif