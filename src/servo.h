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

#define GRABBER_POS_OPEN 75
#define GRABBER_POS_CLOSED 140

#define SLIDER_POS_0 0
#define SLIDER_POS_DEPLOYED 90

#define SERVO_TIP_4 servo_04
#define SERVO_TIP_3 servo_03
#define SERVO_TIP_2 servo_02
#define SERVO_TIP_1 servo_01

#define SERVO_ARM servo_09
#define SERVO_GRABBER servo_08

#define SERVO_SLIDER_1 servo_13
#define SERVO_SLIDER_2 servo_14

void init_servos();
void init_pos();
void disable_servos();
void drop();
void raise();

void update_tippers(int* states);
void update_arm(int pose);
void update_grabber(int pose);
void update_slider(int pose);