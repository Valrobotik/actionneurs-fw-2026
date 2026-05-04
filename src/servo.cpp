#include "servo.h"

Servo servo_01;
Servo servo_02;
Servo servo_03;
Servo servo_04;
Servo servo_05;
Servo servo_06;
Servo servo_07;
Servo servo_08;
Servo servo_09;
Servo servo_10;
Servo servo_11;
Servo servo_12;
Servo servo_13;
Servo servo_14;

void init_servos() {
    servo_01.attach(SERVO_01_PIN);
    servo_02.attach(SERVO_02_PIN);
    servo_03.attach(SERVO_03_PIN);
    servo_04.attach(SERVO_04_PIN);
    servo_05.attach(SERVO_05_PIN);
    servo_06.attach(SERVO_06_PIN);
    servo_07.attach(SERVO_07_PIN);
    servo_08.attach(SERVO_08_PIN);
    servo_09.attach(SERVO_09_PIN);
    servo_10.attach(SERVO_10_PIN);
    servo_11.attach(SERVO_11_PIN);
    servo_12.attach(SERVO_12_PIN);
    servo_13.attach(SERVO_13_PIN);
    servo_14.attach(SERVO_14_PIN);
}

void drop() {
    // Define the MotionGenerator object
    MotionGenerator *trapezoidalProfile = new MotionGenerator(200, 500, 0);

    while (!trapezoidalProfile->getFinished()) {
        // Retrieve calculated position
        float positionRef = 100;
        float position = trapezoidalProfile->update(positionRef);
        Serial.println(position);
        delay(10);
    }
}

void raise() {
}