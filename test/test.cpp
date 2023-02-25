#include "Arduino.h"

void setup(){
Serial.begin(9600);
}

void loop(){
    int btn = digitalRead(5);
    int val = digitalRead(2);
    Serial.println(btn + " " + val);
}