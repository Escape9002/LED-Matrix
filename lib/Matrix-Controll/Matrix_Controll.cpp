#include "Matrix_Controll.h"

Adafruit_NeoPixel pixel;
byte rgb[3];

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

void Matrix_Controll::setColor(byte r, byte g, byte b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

void Matrix_Controll::drawPoint(byte *pos, byte *rgb)
{
    byte shit = generatePos(pos[0], pos[1]);
    pixels.setPixelColor(shit, pixels.Color(rgb[0], rgb[1], rgb[2]));
    pixels.show();
}

void Matrix_Controll::drawRainbow(byte *pos)
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
