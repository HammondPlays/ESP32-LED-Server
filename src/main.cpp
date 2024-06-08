#include <Arduino.h>
#include <animation.h>
#include <wifiService.h>
#include <httpServer.h>

#define DELAY  50

Animation animation = Animation(LED_COUNT, DELAY);

void setup() {
  Serial.begin(9600);
  // Serial.begin(115200);

  WifiService::setup();
  Serial.println(WiFi.localIP());
  animation.setup();

  HttpServer::setup();
}

void loop() {
  HttpServer::loop();
  animation.loop();
  // Serial.println("Running");
}