#include <Arduino.h>
#include <ESP32Servo.h>

#include "pin_definitions.h"
#include "ros.h"

void setup() {
  Serial.begin(115200);
  init_ros();
}

void loop() {
  ros_loop();
  delay(50);
}