#include <Arduino.h>
#include <Servo.h>

Servo myservo;

void setupServo(){
    myservo.attach(10,600,2300);
}

void setSteering(float steering) {
    // steering: -1.0 (left) → 0 → +1.0 (right)

    int centre = 86;
    int range = 40;   

    int angle = centre + steering * range;

    angle = constrain(angle, 40, 130);

    myservo.write(angle);
}