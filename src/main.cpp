//------------------------------------------------------------------------------------------ Hardware
/*
	all digitalpins are destroyed it seems...switch of joystick connected to A5 pressed == 0, otherwise random (debounce for random 0!)
*/

//------------------------------------------------------------------------------------------ Libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include "Joystick.h"
#include "Matrix_Controll.h"

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//------------------------------------------------------------------------------------------ matrix Functions
byte rgb[] = {255, 0, 0}; // red
byte pos[] = {11,11}; // 12*12 matrix

//--------------------------------------------------- set Color
void setColor(byte r, byte g, byte b)
{
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

//--------------------------------------------------- draw point
void drawPoint(byte *pos, byte *rgb)
{
	pixels.setPixelColor(generatePos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
	pixels.show();
}

//--------------------------------------------------- draw rainbow point

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

//------------------------------------------------------------------------------------------ Joystick

//byte pos[] = {6, 6};	  // middle
/*
void setCursorPos(int *cursor)
{
	for (byte i = 0; i < 2; i++)
	{
		if (cursor[i] < 400)
		{

			pos[i] = pos[i] + 1;
			if (pos[i] > 11)
			{
				pos[i] = 11;
			}
		}
		else if (cursor[i] > 600)
		{
			if (pos[i] != 0)
			{
				pos[i] = pos[i] - 1;
			}
			else
			{
				pos[i] = 0;
			}
		}
	}
}*/

//------------------------------------------------------------------------------------------ programms
// still empty =/

//------------------------------------------------------------------------------------------ debugging funcs
#define DEBUG 0

//------------------------------------------------------------------------------------------ change prog
int prog = 0;
int maxProgramms;
volatile byte state = LOW;

void changeProg()
{
	if (prog < (maxProgramms - 1))
	{
		prog++;
	}
	else
	{
		prog = 0;
	}

	state = false;
}

//------------------------------------------------------------------------------------------ check btn press

bool button(uint16_t sw_val)
{
	if (sw_val < 100)
	{
		while (analogRead(A5) < 100)
		{
			// Do nothing debounce | Well whats your name
		}
		return 1;
	}
	return 0;
}

//------------------------------------------------------------------------------------------ setup
int fps;	// higher value, slower game, so 1/fps
unsigned long timer;

void setup()
{
#if DEBUG
	Serial.begin(9600);
	Serial.println("hello");
#endif

	maxProgramms = 2;

	pixels.begin();
	pixels.clear();
	pixels.setBrightness(50);

	fps = 125;
}

//------------------------------------------------------------------------------------------ loop
void loop()
{
#if DEBUG
	bool btn = analogRead(A5);

	Serial.println(btn);
#endif

	if (button(analogRead(A5)))
	{
		changeProg();
	}

	if (timer < millis())
	{
		// x			// y
		int joyStick[] = {analogRead(A2), analogRead(A4)}; // well, whats your pos?
		setCursorPos(joyStick);							   // fuck you pos!

		switch (prog)
		{
		case 0:
			setColor(255, 0, 0);
			drawPoint(pos,rgb) ;
			break;

		case 1:
			drawRainbow(pos);
			break;
		}
		timer = millis() + fps;
	}
}