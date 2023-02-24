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

//------------------------------------------------------------------------------------------ programms
//--------------------------------------------------- draw point
void drawPoint(int *pos, int *rgb)
{
	pixels.setPixelColor(generatepos(pos[0], pos[1]), pixels.Color(rgb[0], rgb[1], rgb[2]));
	pixels.show();
}

//--------------------------------------------------- draw rainbow point
int numColors = 255; 
int counter = 0;

void setColor (int* pos, unsigned char red, unsigned char green, unsigned char blue) 
{   
	int rgb[] = {red, green , blue};
    drawPoint(pos,rgb);
} 

long HSBtoRGB(float _hue, float _sat, float _brightness) {
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    
    if (_sat == 0.0) {
        red = _brightness;
        green = _brightness;
        blue = _brightness;
    } else {
        if (_hue == 360.0) {
            _hue = 0;
        }

        int slice = _hue / 60.0;
        float hue_frac = (_hue / 60.0) - slice;

        float aa = _brightness * (1.0 - _sat);
        float bb = _brightness * (1.0 - _sat * hue_frac);
        float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
        
        switch(slice) {
            case 0:
                red = _brightness;
                green = cc;
                blue = aa;
                break;
            case 1:
                red = bb;
                green = _brightness;
                blue = aa;
                break;
            case 2:
                red = aa;
                green = _brightness;
                blue = cc;
                break;
            case 3:
                red = aa;
                green = bb;
                blue = _brightness;
                break;
            case 4:
                red = cc;
                green = aa;
                blue = _brightness;
                break;
            case 5:
                red = _brightness;
                green = aa;
                blue = bb;
                break;
            default:
                red = 0.0;
                green = 0.0;
                blue = 0.0;
                break;
        }
    }

    long ired = red * 255.0;
    long igreen = green * 255.0;
    long iblue = blue * 255.0;
    
    return long((ired << 16) | (igreen << 8) | (iblue));
}

void drawRainbow(int* pos, int fps){
	// This part takes care of displaying the
  // color changing in reverse by counting backwards if counter
  // is above the number of available colors  
  float colorNumber = counter > numColors ? counter - numColors: counter;
  
  // Play with the saturation and brightness values
  // to see what they do
  float saturation = 1; // Between 0 and 1 (0 = gray, 1 = full color)
  float brightness = .05; // Between 0 and 1 (0 = dark, 1 is full brightness)
  float hue = (colorNumber / float(numColors)) * 360; // Number between 0 and 360
  long color = HSBtoRGB(hue, saturation, brightness); 
  
  // Get the red, blue and green parts from generated color
  int red = color >> 16 & 255;
  int green = color >> 8 & 255;
  int blue = color & 255;

  setColor(pos, red, green, blue);
  
  // Counter can never be greater then 2 times the number of available colors
  // the colorNumber = line above takes care of counting backwards (nicely looping animation)
  // when counter is larger then the number of available colors
  counter = (counter + 1) % (numColors * 2);
  
  // If you uncomment this line the color changing starts from the
  // beginning when it reaches the end (animation only plays forward)
  // counter = (counter + 1) % (numColors);

  delay(fps);
}

//------------------------------------------------------------------------------------------ Joystick

int pos[] = {6, 6};		 // middle
int rgb[] = {255, 0, 0}; // red

void cursor(int* cursor)
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

		switch(prog){
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