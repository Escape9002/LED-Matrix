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
int delayval = 10;
int yPin = A4;
int xPin = A2;

int courser[] = {5,5};
int weg[144][2];
int wegindex = 0;
int rgb[] = {0,255,0};
boolean isrunning =true;


//------------------------------------------------------------------------------------------ Smileys to show ^^
#include "Smileys.h"
Smileys smileys;

byte smil = 0;
byte smil_min = 0;
byte smil_max = 3;

void drawMatrix(bool matrixArr[12][12], byte *pos, byte *rgb)
{

	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			pos[0] = x;
			pos[1] = y;
    }

			if (matrixArr[x][y] == 1)
			{
				matrix.setColor(128, 128, 128, rgb);
			}
			else
			{
				matrix.setColor(0, 0, 64, rgb);
			}

			matrix.drawPoint(pos, rgb);
		}
	}
}
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

	maxProgramms = 3;

	pixels.begin();
	pixels.clear();
	pixels.setBrightness(25);

	matrix.setColor(255, 0, 0, rgb);

	fps = 125;
	randomSeed(analogRead(0));
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
			matrix.setColor(0, 0, 255, rgb);
			matrix.drawPoint(pos, rgb);
			break;

		case 1:
			matrix.drawRainbow(pos);
			break;

		case 2:
			switch (joystick.getCursorDir(cursorVals[0], cursorVals[1]))
			{
			case joystick.UP:
				if (smil < (smil_max - 1))
				{
					smil++;
				}
				else
				{
					smil = 0;
				}
				break;

			case joystick.DOWN:
				if (smil > smil_min)
				{
					smil--;
				}
				else
				{
					smil = smil_max - 1;
				}
				break;

			case joystick.LEFT:
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

				break;

			case joystick.RIGHT:
				rgb[0] = rgb[0] - 5;
				rgb[1] = rgb[1] - 25;
				rgb[2] = rgb[2] - 50;

				for (byte i = 3; i > 0; i--)
				{
					if (rgb[i] < 0)
					{
						rgb[i] = 255;
					}
				}
				break;
			}
			drawMatrix(smileys.SmileArray[smil], pos, rgb);
			break;
		}
		timer = millis() + fps;
	}
}





while(isrunning == true){
// Begin Move-Check
	if(analogRead(yPin) != 511){
		if(analogRead(yPin) < 411){
			if(courser[1] != 11){
				courser[1] ++;
				
			}
		}
		if(analogRead(yPin) > 611){
			if(courser[1] != 0){
				courser[1] --;
				
			}
		}
	}
	if(analogRead(xPin) != 526){
		if(analogRead(xPin) < 426){
			if(courser[0] != 11){
				courser[0] ++;
				
			}
		}
		if(analogRead(xPin) > 611){
			if(courser[0] != 0){
				courser[0] --;
				
			}
		}
	}	

	drawPoint(courser,rgb);

	pixels.show();
	delay(100);
	// End Move-Check

pixels.show();
// Weg Schreiben	
	if((weg[wegindex][0] != courser[0]) || (weg[wegindex][1] != courser[1] )){
		weg[wegindex+1][0] = courser[0];
		weg[wegindex+1][1] = courser[1];
	}
//Kollision
 	for(int f = 0; f <= wegindex;  f++ ){
		if((weg[f][0] == courser[0]) && (weg[f][1]== courser [1])){
			isrunning =false;
			pixels.clear();
		}
	}
}
while(isrunning ==false){
	for(int i =0; i < 25; i++){
	pixels.fill(pixels.Color(255,0,0),0,144);pixels.show();
	delay(100);
	pixels.clear();pixels.show();
	delay(100);
	}
	

}
}
