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

void testMotor(){
    //Smooth ramp
    for (int speed=0; speed<=30; speed++){
        analogWrite(LPWM, speed);
        analogWrite(RPWM, 0);
        delay(10);
    }
    delay(3000);
    for (int speed=30; speed>=0; speed--){
        analogWrite(LPWM, speed);
        analogWrite(RPWM, 0);
        delay(10);
    }

    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
    delay(1000);

    for (int speed=0; speed<=30; speed++){
        analogWrite(RPWM, speed);
        analogWrite(LPWM, 0);
        delay(10);
    }
    delay(3000);
    for (int speed=30; speed>=0; speed--){
        analogWrite(RPWM, speed);
        analogWrite(LPWM, 0);
        delay(10);
    }
    
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
    delay(1000);
    Serial.println("Testing Complete :D");
}