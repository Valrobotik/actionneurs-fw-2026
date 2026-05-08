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

#define SERVOCHECK(fn) { int temp_rc = fn; if((!temp_rc)){Serial.println("Erreur Servo");} \
    else {Serial.printf("Attached to channel: %d", temp_rc);}}

void init_servos() {
    SERVOCHECK(servo_01.attach(SERVO_01_PIN));
    SERVOCHECK(servo_02.attach(SERVO_02_PIN));
    SERVOCHECK(servo_03.attach(SERVO_03_PIN));
    SERVOCHECK(servo_04.attach(SERVO_04_PIN));
    SERVOCHECK(servo_05.attach(SERVO_05_PIN));
    SERVOCHECK(servo_06.attach(SERVO_06_PIN));
    SERVOCHECK(servo_07.attach(SERVO_07_PIN));
    SERVOCHECK(servo_08.attach(SERVO_08_PIN));
    SERVOCHECK(servo_09.attach(SERVO_09_PIN));
    SERVOCHECK(servo_10.attach(SERVO_10_PIN));
    SERVOCHECK(servo_11.attach(SERVO_11_PIN));
    SERVOCHECK(servo_12.attach(SERVO_12_PIN));
    SERVOCHECK(servo_13.attach(SERVO_13_PIN));
    SERVOCHECK(servo_14.attach(SERVO_14_PIN));
}

void drop() {
    // Define the MotionGenerator object
    MotionGenerator *trapezoidalProfile = new MotionGenerator(50, 500, 0);

    while (!trapezoidalProfile->getFinished()) {
        // Retrieve calculated position
        float positionRef = 100;
        float position = trapezoidalProfile->update(positionRef);
        Serial.println(position);
        servo_11.write(position);
        delay(10);
    }
}

void raise() {
}