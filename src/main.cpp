#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <animation.h>

#define LED_PIN   2
#define LED_COUNT 3
#define DELAY     50

Adafruit_NeoPixel stripe = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Animation animation = Animation(stripe, LED_COUNT, DELAY);

void setup() {
  
  animation.setup();
  Serial.begin(9600);
}

void loop() {
  //Serial.println(animation.color);
  animation.boomerang();
}


