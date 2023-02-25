#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 1
#define NUMPIXELS 12 * 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;
int yPin = A4;
int xPin = A2;

int courser[] = {5,5};
int weg[144][2];
int wegindex = 0;
int rgb[] = {0,255,0};
boolean isrunning =true;



void setup()
{
	pixels.begin();
	//Serial.begin(9600);
	
	pinMode(5,INPUT);


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


void loop()
{




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
