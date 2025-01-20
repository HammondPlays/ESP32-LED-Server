#include "animationType.h"

std::map<AnimationType, std::string> getAnimationTypeMap() {
    return {
        {BOOMERANG, "BOOMERANG"},
        {RAINBOW, "RAINBOW"}
    };
}

String getAnimationTypeJson() {
    DynamicJsonDocument doc(1024);
    auto animationTypeMap = getAnimationTypeMap();
    for (const auto& animation : animationTypeMap) {
        doc[String(animation.first)] = animation.second;
    }
    String json;
    serializeJson(doc, json);
    return json;
}