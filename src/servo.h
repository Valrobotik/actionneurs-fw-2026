#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

#include "MotionGenerator.h"
#include "pin_definitions.h"

void init_servos();
void drop();
void raise();