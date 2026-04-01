#include <Arduino.h>
<<<<<<< HEAD
#include "steering.h"
#include "motor_commands.h"

void setup(){
    setupMotor();
    setupServo();
    Serial.begin(115200);
    Serial.setTimeout(10);
    setSteering(0.0);
    setThrottle(0);
    updateMotor();
=======
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
>>>>>>> a82512f53b9c5796fb3547d44d7b6ae81869d091
}

void loop(){

    if (Serial.available() > 0){
<<<<<<< HEAD
    String msg = Serial.readStringUntil('\n');

    int throttle = 0;
    float steering = 0.0;

    Serial.println("RAW: " + msg);

    if (sscanf(msg.c_str(), "%d,%f", &throttle, &steering) == 2){
        setThrottle(throttle);
        setSteering(steering);
        
        //debugging
        Serial.println("RX: Throttle " + String(throttle) + " Steering " + String(steering));
    }
}
updateMotor();
=======
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
>>>>>>> a82512f53b9c5796fb3547d44d7b6ae81869d091
}