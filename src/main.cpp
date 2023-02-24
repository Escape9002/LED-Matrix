#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;

void setup()
{
	pixels.begin();
	//Serial.begin(9600);
}

int generatepos(int x, int y){

	if(y % 2 == 1){
		return ((11-x )+ 12*y);
	}else{
		return (x + 12*y);
	}
}

void matrix(int* pos, int* rgb){
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
}

void drawPoint(int* pos, int* rgb){
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
	pixels.show();
}

int * move(int * courser){
	return courser;
}

int pos[] = {72,72};
int rgb[] = {0,0,255};

void loop()
{
	int x = analogRead(A4);
	int y = analogRead(A2);

	if((x-20) < x || x < (x+20)){

	}else{
		pos[0] = pos[0] - map(x,0,1024,-72,72);
		pos[1] = pos[1] - map(y,0,1024,-72,72);
		drawPoint(pos, rgb);
	}
	
	
}
