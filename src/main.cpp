//------------------------------------------------------------------------------------------ Hardware
/*
	all digitalpins are destroyed it seems...switch of joystick connected to A5 pressed == 0, otherwise random (debounce for random 0!)
*/

//------------------------------------------------------------------------------------------ Libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//------------------------------------------------------------------------------------------ matrix Functions

int generatepos(byte x, byte y)
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

void matrix(byte *pos, byte *rgb)
{
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
}

//------------------------------------------------------------------------------------------ Joystick

byte pos[] = {6, 6};	  // middle
byte rgb[] = {255, 0, 0}; // red

void setCursorPos(int *cursor)
{
	for (byte i = 0; i < 2; i++)
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
}

//------------------------------------------------------------------------------------------ programms
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
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
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

//------------------------------------------------------------------------------------------ debugging funcs
#define DEBUG 0

void debug()
{
	for (byte i = 0; i < 13; i++)
	{
		pos[0] = i;
		pos[1] = i;
		drawPoint(pos, rgb);
		delay(100);
	}
}

//------------------------------------------------------------------------------------------ change prog
int prog = 0;
int maxProgramms;
volatile byte state = LOW;

void changeProg()
{
	if (state)
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
	else
	{
		state = true;
	}
}

//------------------------------------------------------------------------------------------ check btn press
byte btn_counter = 0;

bool button(int sw_val)
{
	if (sw_val < 10)
	{
		btn_counter++;

#if DEBUG
		Serial.println(btn_counter);
#endif

		if (btn_counter > 15)
		{
#if DEBUG
			Serial.println(" Hello");
#endif
			btn_counter = 0; // Well then fuck you Toni
			while (analogRead(A5) < 10)
			{
				// Do nothing debounce | Well whats your name
			}
			return 1;
		}
	}
	else
	{

		btn_counter = 0;
		return 0;
	}
}

//------------------------------------------------------------------------------------------ setup
int fps;
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
	pixels.setBrightness(100);

	fps = 100;
}

//------------------------------------------------------------------------------------------ loop
void loop()
{
#if DEBUG
	bool btn = analogRead(A5);

	Serial.println(btn);
#endif

	if (timer < millis())
	{
		// x			// y
		int joyStick[] = {analogRead(A2), analogRead(A4)}; // well, whats your pos?
		setCursorPos(joyStick);							   // fuck you pos!

		switch (prog)
		{
		case 0:
			setColor(255, 0, 0);
			drawPoint(pos, rgb);
			break;

		case 1:
			drawRainbow(pos);
			break;
		}
		timer = millis() + fps;
	}

	if (button(analogRead(A5)))
	{
		changeProg();
	}
}