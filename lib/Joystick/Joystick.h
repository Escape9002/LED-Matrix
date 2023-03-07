#include "Arduino.h"

class Joystick{
    public:
        enum JoystickStates {UP, DOWN, LEFT, RIGHT, DEADZONE};
        JoystickStates getCursorDir (int x, int y);
        byte* setCursorPos(byte* pos, int* JoystickVal);
        bool button(int sw_val, uint8_t btn_pin);
        byte clam(int pos, byte min, byte max);
};