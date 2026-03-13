# include <Arduino.h>

#define RPWM 5
#define LPWM 6
#define R_EN 7
#define L_EN 8

void setupMotor() {
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);

    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);
}

void brake_f(){
    for (int speed=30; speed>=0; speed--){
        analogWrite(LPWM, speed);
        analogWrite(RPWM, 0);
        delay(5);
    }
}

void brake_r(){
    for (int speed=30; speed>=0; speed--){
        analogWrite(LPWM, 0);
        analogWrite(RPWM, speed);
        delay(5);
    }
}

void throttle(){
    brake_r();
    for (int speed=0; speed<=30; speed++){
        analogWrite(LPWM, speed);
        analogWrite(RPWM, 0);
        delay(10);
    }
}


void reverse(){
    brake_f();
    for (int speed=0; speed<=30; speed++){
        analogWrite(RPWM, speed);
        analogWrite(LPWM, 0);
        delay(10);
    }
}

void stop(){
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
}