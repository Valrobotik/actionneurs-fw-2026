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
    else {Serial.printf("Attached to channel: %d\n", temp_rc);}}

void init_servos() {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    // if (!ledcAttach(SERVO_02_PIN, 50, 10)) {
    //     Serial.println("aaaaaaaaaaa");
    //     delay(10000);
    // }
    // ledcAttach(SERVO_02_PIN, 50, 10);
    // ledcAttach(SERVO_03_PIN, 50, 10);
    // ledcAttach(SERVO_04_PIN, 50, 10);
    SERVOCHECK(servo_01.attach(SERVO_01_PIN));
    SERVOCHECK(servo_02.attach(SERVO_02_PIN));
    SERVOCHECK(servo_03.attach(SERVO_03_PIN));
    SERVOCHECK(servo_04.attach(SERVO_04_PIN));
    // SERVOCHECK(servo_05.attach(SERVO_05_PIN));
    // SERVOCHECK(servo_06.attach(SERVO_06_PIN));
    // SERVOCHECK(servo_07.attach(SERVO_07_PIN));
    SERVOCHECK(servo_08.attach(SERVO_08_PIN));
    SERVOCHECK(servo_09.attach(SERVO_09_PIN));
    // SERVOCHECK(servo_10.attach(SERVO_10_PIN));
    // SERVOCHECK(servo_11.attach(SERVO_11_PIN));
    // SERVOCHECK(servo_12.attach(SERVO_12_PIN));
    SERVOCHECK(servo_13.attach(SERVO_13_PIN));
    SERVOCHECK(servo_14.attach(SERVO_14_PIN));
}

void init_pos() {
    SERVO_TIP_1.write(TIPPER_POS_0);
    SERVO_TIP_2.write(TIPPER_POS_0);
    SERVO_TIP_3.write(TIPPER_POS_0);
    SERVO_TIP_4.write(TIPPER_POS_0);

    SERVO_ARM.write(ARM_POS_0);
    SERVO_GRABBER.write(GRABBER_POS_OPEN);

    SERVO_SLIDER_1.write(SLIDER_POS_0);
    SERVO_SLIDER_2.write(SLIDER_POS_0);
}

void disable_servos() {
    servo_01.detach();
    servo_02.detach();
    servo_03.detach();
    servo_04.detach();
    servo_05.detach();
    servo_06.detach();
    servo_07.detach();
    servo_08.detach();
    servo_09.detach();
    servo_10.detach();
    servo_11.detach();
    servo_12.detach();
    // SERVOCHECK(servo_13.attach(SERVO_13_PIN));
    // SERVOCHECK(servo_14.attach(SERVO_14_PIN));
}

void drop() {
    // Define the MotionGenerator object
    MotionGenerator *trapezoidalProfile = new MotionGenerator(50, 50, 90);
    float positionRef;
    positionRef = 150;
    while (!trapezoidalProfile->getFinished()) {
        float position = trapezoidalProfile->update(positionRef);
        Serial.println(position);
        // float value = map(position, 0, 180, DEFAULT_uS_LOW, DEFAULT_uS_HIGH);
        // ledcWrite(SERVO_02_PIN, value);
        // SERVO_TIP_3.write(TIPPER_POS_0);
        SERVO_TIP_1.write(position);
        SERVO_TIP_2.write(position);
        SERVO_TIP_3.write(position);
        SERVO_TIP_4.write(position);
        delay(25);
    }
    positionRef = 90;
    trapezoidalProfile->update(positionRef);
    while (!trapezoidalProfile->getFinished()) {
        float position = trapezoidalProfile->update(positionRef);
        Serial.println(position);
        // float value = map(position, 0, 180, DEFAULT_uS_LOW, DEFAULT_uS_HIGH);
        // ledcWrite(SERVO_02_PIN, value);
        // SERVO_TIP_3.write(TIPPER_POS_0);
        SERVO_TIP_1.write(position);
        SERVO_TIP_2.write(position);
        SERVO_TIP_3.write(position);
        SERVO_TIP_4.write(position);
        delay(25);
    }
    // MotionGenerator *trapezoidalProfile_2 = new MotionGenerator(100, 50, 90);
    // float positionRef_2;
    // positionRef_2 = 180;
    // while (!trapezoidalProfile_2->getFinished()) {
    //     float position_2 = trapezoidalProfile_2->update(positionRef_2);
    //     Serial.println(position_2);
    //     // float value = map(position, 0, 180, DEFAULT_uS_LOW, DEFAULT_uS_HIGH);
    //     // ledcWrite(SERVO_02_PIN, value);
    //     // SERVO_TIP_3.write(TIPPER_POS_0);
    //     SERVO_TIP_1.write(position_2);
    //     delay(25);
    // }
    // positionRef_2 = 90;
    // trapezoidalProfile_2->update(positionRef_2);
    // while (!trapezoidalProfile_2->getFinished()) {
    //     float position_2 = trapezoidalProfile_2->update(positionRef_2);
    //     Serial.println(position_2);
    //     // float value = map(position, 0, 180, DEFAULT_uS_LOW, DEFAULT_uS_HIGH);
    //     // ledcWrite(SERVO_02_PIN, value);
    //     // SERVO_TIP_3.write(TIPPER_POS_0);
    //     SERVO_TIP_1.write(position_2);
    //     delay(25);
    // }
}

void raise() {
}

void update_tippers(int* states) {
  SERVO_TIP_1.write(states[0]);
  SERVO_TIP_2.write(states[1]);
  SERVO_TIP_3.write(states[2]);
  SERVO_TIP_4.write(states[3]);
}

void update_arm(int pose) {
    MotionGenerator *trapezoidalProfile = new MotionGenerator(50, 50, SERVO_ARM.read());
    while (!trapezoidalProfile->getFinished()) {
        float position = trapezoidalProfile->update(pose);
        SERVO_ARM.write(position);
        delay(25);
    }
}

void update_grabber(int pose) {
    MotionGenerator *trapezoidalProfile = new MotionGenerator(50, 50, SERVO_GRABBER.read());
    while (!trapezoidalProfile->getFinished()) {
        float position = trapezoidalProfile->update(pose);
        SERVO_GRABBER.write(position);
        delay(25);
    }
}

void update_slider(int pose) {
    MotionGenerator *trapezoidalProfile = new MotionGenerator(50, 50, SERVO_SLIDER_1.read());
    while (!trapezoidalProfile->getFinished()) {
        float position = trapezoidalProfile->update(pose);
        SERVO_SLIDER_1.write(position);
        SERVO_SLIDER_2.write(-position);
        delay(25);
    }
}