#include "animationType.h"

std::map<AnimationType, AnimationDetails> getAnimationTypeMap() {
    return {
        {BOOMERANG, {"BOOMERANG", {"SPEED"}}},
        {RAINBOW, {"RAINBOW", {}}},
        {STATIC, {"STATIC", {"COLOR"}}}
    };
}

String getAnimationTypeJson() {
    DynamicJsonDocument doc(1024);
    auto animationTypeMap = getAnimationTypeMap();

    for (const auto& animation : animationTypeMap) {
        JsonObject animationObject = doc.createNestedObject(String(animation.first));
        animationObject["name"] = animation.second.name;

        JsonArray parameters = animationObject.createNestedArray("parameters");
        for (const auto& param : animation.second.animationParameters) {
            parameters.add(param);
        }
    }

    String json;
    serializeJson(doc, json);
    return json;
}

/*String getAnimationTypeJson() {
    DynamicJsonDocument doc(1024);
    auto animationTypeMap = getAnimationTypeMap();
    for (const auto& animation : animationTypeMap) {
        doc[String(animation.first)] = animation.second;
    }
    String json;
    serializeJson(doc, json);
    return json;
}*/