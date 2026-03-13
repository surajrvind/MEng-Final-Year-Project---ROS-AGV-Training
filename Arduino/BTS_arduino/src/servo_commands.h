#include <Arduino.h>
#include <Servo.h>

Servo myservo;

void setupServo(){
    myservo.attach(10,600,2300);
}

int current = myservo.read();

void left(){
    for (int angle=current; angle <=130; angle++){
        myservo.write(angle);
        delay(10);
    }
}

void right(){
    for (int angle=current; angle >=40; angle--){
        myservo.write(angle);
        delay(10);
    }
}

void centre(){
    if (myservo.read() != 86){
        myservo.write(86);
    }
}