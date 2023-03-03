#ifndef H_Joystick;
#define H_Joystick;

class Joystick{
    public:
        enum JoystickStates {UP, DOWN, LEFT, RIGHT, DEADZONE};
        JoystickStates setCursorPos (int x, int y);
};

#endif