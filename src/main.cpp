#include <Arduino.h>

#include "pin_definitions.h"
#include "ros.h"
#include "servo.h"

void setup() {
  Serial.begin(115200);
  init_servos();
  drop();
  init_ros();
}

void loop() {
  ros_loop();
  delay(50);
}