#include "ledMode.h"

std::map<LedMode, LedModeDetails> getLedModeMap() {
    return {
        {STRIPE, {"STRIPE", {"LED_COUNT"}}},
        {SHAPE,{"SHAPE", {"LED_COUNT", "SHAPE_SIZE", "SHAPE_COUNT"}}}
    };
}

String getLedModeJson() {
    DynamicJsonDocument doc(1024);
    auto ledModeMap = getLedModeMap();
    
    for (const auto& mode : ledModeMap) {
        JsonObject animationObject = doc.createNestedObject(String(mode.first));
        animationObject["name"] = mode.second.name;

        JsonArray parameters = animationObject.createNestedArray("parameters");
        for (const auto& param : mode.second.ledModeParameters) {
            parameters.add(param);
        }
    }

    String json;
    serializeJson(doc, json);
    return json;
}