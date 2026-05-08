#include <Arduino.h>
#include <FastLED.h>

#include "pin_definitions.h"
#include "ros.h"
#include "servo.h"

CRGB led[1];

extern states state;

void LightTask(void *pvParams) {
  Serial.println("Started light task");
  while (1) {
    // switch (motors_state) {
    // case motors_state_t::OFF:
    //   led[0] = CRGB::Red1;
    //   break;
    // case motors_state_t::TURNING:
    //   led[0] = CRGB::Yellow2;
    //   break;
    // case motors_state_t::FORWARD:
    //   led[0] = CRGB::Blue2;
    //   break;
    // case motors_state_t::WAITING:
    //   led[0] = CRGB::Green;
    //   break;
    // }
    led[0] = CRGB::Green3;
    if ((millis() % 5000) < 30) {
      led[0] = CRGB::White;
    }
    if (state != states::AGENT_CONNECTED && (millis() % 500) < 200 && (millis() % 500) > 100) {
      led[0] = CRGB::Purple;
    }
    FastLED.show();
    delay(20);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("bf lkeds");
  delay(100),
  FastLED.addLeds<WS2812B, RGB_LED_PIN, GRB>(led, 1);
  delay(100),
  Serial.println("leds added");
  delay(100),
  xTaskCreatePinnedToCore(LightTask, "LightTask", 2048, NULL, 2, NULL, 1);
  init_servos();
  delay(1000);
  drop();
  drop();
  drop();
  drop();
  init_ros();
  delay(10000);
  // disable_servos();
}

void loop() {
  ros_loop();
  delay(50);
}