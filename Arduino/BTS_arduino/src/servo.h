#include <Arduino.h>
#include <Servo.h>

Servo myservo;

void setupServo(){
    myservo.attach(10,600,2300);
}

void testServo(){
    //left
    myservo.write(86);
    delay(1000);
    myservo.write(130);
    delay(1000);
    //right
    myservo.write(86);
    delay(1000);
    myservo.write(40);
    delay(2000);

    for (int angle=40; angle <=130; angle++){
        myservo.write(angle);
        delay(5);
    }
    delay(1000);
    for (int angle=130; angle >=40; angle--){
        myservo.write(angle);
        delay(5);
    }
    delay(1000);
    myservo.write(86);

    delay(500);
    Serial.println("Testing done");
}

void left(){

}