#ifndef TestLEDs_H
#define TestLEDs_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

class TestLEDs
{
private:
    int a=0;
    int b= 0;
    int c=255;

    int NUMPIXELS;
    int PIN;
    Adafruit_NeoPixel pixels;

public:
    TestLEDs(int NUMPIXELS, int PIN, Adafruit_NeoPixel pixel);
    void fill(int wait);
    void say(String msg);

protected:
};
#endif