#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Matrix_Controll
{
public:
    Matrix_Controll(Adafruit_NeoPixel pixels);
    byte generatePos(byte x, byte y);
    boolean checkWall(byte *pos);

    void setColor(byte r, byte g, byte b, byte* rgb);
    void drawPoint(byte *pos, byte *rgb);
    void drawRainbow(byte *pos);
};