//------------------------------------------------------------------------------------------ Hardware
/*
	all digitalpins are destroyed it seems...switch of joystick connected to A5 pressed == 0, otherwise random (debounce for random 0!) is pulled high, pressed by val = 0; not pressed by val > 500
*/

//------------------------------------------------------------------------------------------ Libraries
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#include "Joystick.h"
#include "Matrix_Control.h"

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
byte rgb[] = {255, 0, 0}; // red
byte pos[] = {6, 6};	  // 12*12 matrix

Matrix_Controll matrix = Matrix_Controll(pixels);
Joystick joystick;

//------------------------------------------------------------------------------------------ debugging funcs
#define DEBUG 0

//------------------------------------------------------------------------------------------ change prog
int prog = 0;
int maxProgramms;

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
}

//------------------------------------------------------------------------------------------ setup
int fps; // higher value, slower game, so 1/fps
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

	matrix.setColor(255, 0, 0, rgb);

	fps = 125;
}

//------------------------------------------------------------------------------------------ loop
void loop()
{
#if DEBUG
	bool btn = analogRead(A5);

	Serial.println(btn);
#endif

	if (joystick.button(analogRead(A5), A5))
	{
		changeProg();
	}

	if (timer < millis())
	{
		int cursorVals[] = {analogRead(A2), analogRead(A4)};
		joystick.setCursorPos(pos, cursorVals);

		switch (prog)
		{
		case 0:
			matrix.setColor(255, 0, 0, rgb);
			matrix.drawPoint(pos, rgb);
			break;

		case 1:
			matrix.drawRainbow(pos);
			break;
		}
		timer = millis() + fps;
	}
}