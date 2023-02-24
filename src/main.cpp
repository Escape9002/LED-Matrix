//------------------------------------------------------------------------------------------ Libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//------------------------------------------------------------------------------------------ matrix Functions

int generatepos(int x, int y)
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

void matrix(int *pos, int *rgb)
{
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
}

//------------------------------------------------------------------------------------------ Joystick

int pos[] = {6, 6};		 // middle
int rgb[] = {255, 0, 0}; // red

void cursor(int *cursor)
{
	for (int i = 0; i < 2; i++)
	{
		if (cursor[i] < 200)
		{

			pos[i] = pos[i] + 1;
			if (pos[i] > 11)
			{
				pos[i] = 11;
			}
		}
		else if (cursor[i] > 800)
		{

			pos[i] = pos[i] - 1;
			if (pos[i] < 0)
			{
				pos[i] = 0;
			}
		}
	}
}

//------------------------------------------------------------------------------------------ programms
//--------------------------------------------------- draw point
void drawPoint(int *pos, int *rgb)
{
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
	pixels.show();
}

//--------------------------------------------------- draw rainbow point

void drawRainbow(int *pos)
{
	rgb[0] = rgb[0] + 5;
	rgb[1] = rgb[1] + 25;
	rgb[2] = rgb[2] + 50;

	for (int i = 3; i > 0; i--)
	{
		if (rgb[i] > 255)
		{
			rgb[i] = 0;
		}
	}

	drawPoint(pos, rgb);
}

//------------------------------------------------------------------------------------------ debugging funcs
void debug()
{
	for (int i = 0; i < 13; i++)
	{
		pos[0] = i;
		pos[1] = i;
		drawPoint(pos, rgb);
		delay(100);
	}
}

//------------------------------------------------------------------------------------------ change prog
int prog;
int maxProgramms;

void changeProg()
{
	if (prog < maxProgramms)
	{
		prog++;
	}
	else
	{
		prog = 0;
	}
}

//------------------------------------------------------------------------------------------ setup
const byte interruptPin = 5; // interruptPin
volatile byte state = LOW;

int fps;
long timer = millis() + fps;
void setup()
{

	maxProgramms = 2;
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptPin), changeProg, CHANGE);

	pixels.begin();
	pixels.clear();

	fps = 100;
}

//------------------------------------------------------------------------------------------ loop
void loop()
{

	if (timer < millis())
	{

		int joyStick[] = {analogRead(A2), analogRead(A4)};
		cursor(joyStick);

		switch (prog)
		{
		case 0:
			drawPoint(pos, rgb);
			break;

		case 1:
			drawRainbow(pos, fps);
			break;
		}
		timer = millis() + fps;
	}
}