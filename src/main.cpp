#include <Arduino.h>
#include <ESP32Servo.h>

#include "pin_definitions.h"
#include "ros.h"
#include "servo.h"

void setup() {
  Serial.begin(115200);
  drop();
  init_ros();
}

void loop() {
  ros_loop();
  delay(50);
}