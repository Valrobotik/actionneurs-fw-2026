#include "servo.h"

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