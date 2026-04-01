#include <Arduino.h>
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
}

void loop(){

    if (Serial.available() > 0){
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
}