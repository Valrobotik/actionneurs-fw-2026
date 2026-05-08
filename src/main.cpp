#include <Arduino.h>
#include <FastLED.h>

#include "pin_definitions.h"
#include "ros.h"
#include "servo.h"

CRGB led[1];

extern states state;
extern servos_state_t servos_state;

void LightTask(void *pvParams) {
  Serial.println("Started light task");
  while (1) {
    switch (servos_state) {
    case servos_state_t::OFF:
      led[0] = CRGB::Red1;
      break;
    case servos_state_t::MOVING:
      led[0] = CRGB::Blue2;
      break;
    case servos_state_t::HOLDING:
      led[0] = CRGB::Green3;
      break;
    }
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
  FastLED.addLeds<WS2812B, RGB_LED_PIN, GRB>(led, 1);
  xTaskCreatePinnedToCore(LightTask, "LightTask", 2048, NULL, 2, NULL, 1);
  delay(1000); // fake loading ahh
  init_servos();
  init_pos();
  init_ros();
  // delay(2000);
  // int poses[] = {TIPPER_POS_SLIDE, TIPPER_POS_PUSH, TIPPER_POS_SLIDE, TIPPER_POS_PUSH};
  // update_tippers(poses);
  // delay(2000);
  // init_pos();
  // update_arm(ARM_POS_DROP);
  // delay(2000);
  // update_arm(ARM_POS_PICKUP);
  // delay(2000);
  // update_arm(ARM_POS_0);
  // delay(2000);
  // update_grabber(GRABBER_POS_CLOSED);
  // delay(2000);
  // update_slider(true);
  // delay(2000);
  // update_slider(false);
  // delay(2000);
}

void loop() {
  ros_loop();
  delay(50);
}