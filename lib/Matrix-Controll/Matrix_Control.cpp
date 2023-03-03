#include <Arduino.h>
#include "Matrix_Control.h"

Adafruit_NeoPixel pixel;
byte rainbow_rgb[3];

Matrix_Controll::Matrix_Controll(Adafruit_NeoPixel pixels)
{
    pixel = pixels;
}

byte Matrix_Controll::generatePos(byte x, byte y)
{
    if (y % 2 == 1)
    {
        return ((11 - x) + 12 * y);
    }
    else
    {
        return (x + 12 * y);
    }
}

boolean Matrix_Controll::checkWall(byte *pos)
{
    return 0;
}

void Matrix_Controll::setColor(byte r, byte g, byte b, byte* rgb)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

void Matrix_Controll::drawPoint(byte *pos, byte *rgb)
{
    byte shit = generatePos(pos[0], pos[1]);
    pixel.setPixelColor(shit, pixel.Color(rgb[0], rgb[1], rgb[2]));
    pixel.show();
}

void Matrix_Controll::drawRainbow(byte *pos)
{
    rainbow_rgb[0] = rainbow_rgb[0] + 5;
    rainbow_rgb[1] = rainbow_rgb[1] + 25;
    rainbow_rgb[2] = rainbow_rgb[2] + 50;

    for (byte i = 3; i > 0; i--)
    {
        if (rainbow_rgb[i] > 255)
        {
            rainbow_rgb[i] = 0;
        }
    }

    drawPoint(pos, rainbow_rgb);
}
