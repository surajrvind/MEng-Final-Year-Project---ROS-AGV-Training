#include <Arduino.h>
#include "servo_commands.h"
#include "motor_commands.h"

int x;

void setup(){
    setupMotor();
    setupServo();
    Serial.begin(9600);
    Serial.setTimeout(1);

    centre();
    stop();
}

void loop(){

    if (Serial.available() > 0){
        char key = Serial.read();

        switch (key){
            case 'w':
                throttle();
                Serial.println("Throttle...");
                break;
            case 'a':
                left();
                Serial.println("Going left...");
                break;
            case 's':
                reverse();
                Serial.println("Reversing...");
                break;
            case 'd':
                right();
                Serial.println("Going right...");
                break;
            case 'x':
                brake_f();
                Serial.println("HOL UP");
                break;
            case 'c':
                centre();
                Serial.println("Straightening...");
                break;
        }
    }
}