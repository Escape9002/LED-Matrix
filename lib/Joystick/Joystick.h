#include "Arduino.h"

class Joystick{
    public:
        enum JoystickStates {UP, DOWN, LEFT, RIGHT, DEADZONE};
        JoystickStates getCursorDir (int x, int y);
        byte* setCursorPos(byte* pos, int* JoystickVal);
        byte clam(int pos, byte min, byte max);
};