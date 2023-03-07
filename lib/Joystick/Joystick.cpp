#include "Joystick.h"

Joystick::JoystickStates Joystick::getCursorDir(int x, int y)
{
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

byte *Joystick::setCursorPos(byte *pos, int *JoystickVal)
{
	for (byte i = 0; i < 2; i++)
	{

		if (JoystickVal[i] < 400)
		{

			pos[i] = pos[i] + 1;
			if (pos[i] > 11)
			{
				pos[i] = 11;
			}
		}

		else if (JoystickVal[i] > 600)
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

	return pos;
}

bool Joystick::button(int sw_val, uint8_t btn_pin)
{
	if (sw_val < 100)
	{
		while (analogRead(btn_pin) < 100)
		{
			// Do nothing debounce | Well whats your name
		}
		return 1;
	}
	return 0;
}

byte Joystick::clam(int pos, byte min, byte max)
{
	if (pos < min)
	{
		return min;
	}
	if (pos > max)
	{
		return max;
	}

	return pos;
}