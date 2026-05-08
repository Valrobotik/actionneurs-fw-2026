#pragma once

#include <Arduino.h>
#include <ESP32Servo.h>

#include "MotionGenerator.h"
#include "pin_definitions.h"

#define TIPPER_POS_0 110
#define TIPPER_POS_PUSH 140
#define TIPPER_POS_SLIDE 40

#define ARM_POS_0 90-15
#define ARM_POS_DROP 90-5
#define ARM_POS_PICKUP 90+60

#define SERVO_TIP_4 servo_04
#define SERVO_TIP_3 servo_03
#define SERVO_TIP_2 servo_02
#define SERVO_TIP_1 servo_01

#define SERVO_ARM servo_09

void init_servos();
void init_pos();
void disable_servos();
void drop();
void raise();

void update_tippers(int* states);
void update_arm(int pose);