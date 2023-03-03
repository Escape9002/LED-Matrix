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
Matrix_Controll matrix = Matrix_Controll(pixels);
Joystick joystick;

//------------------------------------------------------------------------------------------ matrix vals
// byte rgb[] = {255, 0, 0}; // red
byte pos[] = {11,11}; // 12*12 matrix

//------------------------------------------------------------------------------------------ programms
// still empty =/

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
		joystick.setCursorPos(analogRead(A2),analogRead(A4));							   // fuck you pos!

		switch (prog)
		{
		case 0:
			matrix.setColor(255, 0, 0);
			matrix.drawPoint(pos,rgb) ;
			break;

		case 1:
			matrix.drawRainbow(pos);
			break;
		}
		timer = millis() + fps;
	}
}