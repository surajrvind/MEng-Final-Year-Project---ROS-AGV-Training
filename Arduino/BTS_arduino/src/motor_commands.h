# include <Arduino.h>

#define RPWM 5
#define LPWM 6
#define R_EN 7
#define L_EN 8

<<<<<<< HEAD
int speed_current = 0;
int speed_target = 0;

=======
>>>>>>> a82512f53b9c5796fb3547d44d7b6ae81869d091
void setupMotor() {
    pinMode(RPWM, OUTPUT);
    pinMode(LPWM, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);

    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);
}

<<<<<<< HEAD
void setThrottle(int mode){
    if (mode == 1) speed_target = 30;
    else if (mode == -1) speed_target = -30;
    else speed_target = 0;
}

void updateMotor(){
    int step = 1;

    if (speed_current < speed_target){  //FORWARD
        speed_current += step;
    }
    else if (speed_current > speed_target){ //REVERSE
        speed_current -= step;
    }

    // Apply direction
    if (speed_current > 0){
        analogWrite(LPWM, speed_current);
        analogWrite(RPWM, 0);
    }
    else if (speed_current < 0){
        analogWrite(RPWM, -speed_current);
        analogWrite(LPWM, 0);
    }
    else{
        analogWrite(LPWM, 0);
        analogWrite(RPWM, 0);
    }
=======
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
>>>>>>> a82512f53b9c5796fb3547d44d7b6ae81869d091
}