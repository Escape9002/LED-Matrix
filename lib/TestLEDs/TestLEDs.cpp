#include <Arduino.h>
#include "TestLEDs.h"

TestLEDs::TestLEDs(int NUMPIXELS, int PIN, Adafruit_NeoPixel pixel)
{
    this->a = 0;
    this->b = 0;
    this->c = 255;

    this->NUMPIXELS = NUMPIXELS;
    this->PIN = PIN;

    this->pixels = pixel;
    pixels.begin();
}

void TestLEDs::fill(int wait)
{
    if (a < 256)
    {
        a = a + 10;
    }
    else
    {
        a = 0;
    }

    if (b < 256)
    {
        b = b + 10;
    }
    else
    {
        b = 0;
    }

    if (c < 256)
    {
        c = c + 10;
    }
    else
    {
        c = 0;
    }
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(a, b, c)); // Moderately bright green color.
        pixels.show();                                  // This sends the updated pixel color to the hardware.
        delay(wait);                                    // Delay for a period of time (in milliseconds).
        Serial.println(i);
    }
    Serial.println("not running");
}

void TestLEDs::say(String msg){
    Serial.println(msg);
}