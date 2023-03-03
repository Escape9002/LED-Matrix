#include "Joystick.h"

// enum Joystick::JoystickStates;

Joystick::JoystickStates Joystick::setCursorPos(int x, int y){
		if (x < 400)
		{
			return LEFT;
		}
		else if (x > 600)
		{
			return RIGHT;
		}

		if (y < 400)
		{
			return UP;
		}
		else if (y > 600)
		{
			return DOWN;
		}

		return DEADZONE;	
}
