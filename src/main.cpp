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
//--------------------------------------------------- set Color
void setColor(int r, int g, int b){
    rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

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
#define DEBUG 0

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
int prog = 0;
int maxProgramms =2;
volatile byte state = LOW;

void changeProg()
{
	if(state){
	if (prog < (maxProgramms-1))
	{
		prog++;
	}
	else
	{
		prog = 0;
	}

	state = false;
	}else{
		state = true;
	}
	
}

//------------------------------------------------------------------------------------------ setup
const byte interruptPin = 2; // interruptPin


int fps;
long timer = millis() + fps;
void setup()
{

	#ifdef DEBUG
		Serial.begin(9600);
	#endif

	maxProgramms = 1;
	pinMode(interruptPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(interruptPin), changeProg, CHANGE);

	pixels.begin();
	pixels.clear();
	pixels.setBrightness(25);

	fps = 100;
}

//------------------------------------------------------------------------------------------ loop
void loop()
{
	#ifdef DEBUG
		bool btn = digitalRead(5);
    	bool val = digitalRead(2);
    	Serial.println(btn + " | " + val);
	#endif

	if (timer < millis())
	{

		int joyStick[] = {analogRead(A2), analogRead(A4)};
		cursor(joyStick);

		switch (prog)
		{
		case 0:
			setColor(255,0,0);
			drawPoint(pos, rgb);
			break;

		case 1:
			drawRainbow(pos);
			break;
		}
		timer = millis() + fps;
	}
}