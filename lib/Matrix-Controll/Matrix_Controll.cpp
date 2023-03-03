#include "Matrix_Controll.h"

Adafruit_NeoPixel pixels;
byte rgb[3];

Matrix_Controll::Matrix_Controll(Adafruit_NeoPixel pixels)
{
    pixels = pixels;
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

void setColor(byte r, byte g, byte b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

void drawPoint(byte *pos, byte *rgb)
{
    byte shit = generatePos(pos[0], pos[1]);
    pixels.setPixelColor(shit, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();
}

void drawRainbow(byte *pos)
{
    rgb[0] = rgb[0] + 5;
    rgb[1] = rgb[1] + 25;
    rgb[2] = rgb[2] + 50;

    for (byte i = 3; i > 0; i--)
    {
        if (rgb[i] > 255)
        {
            rgb[i] = 0;
        }
    }

    drawPoint(pos, rgb);
}
