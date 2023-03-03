class Joystick{
    public:
        enum JoystickStates {UP, DOWN, LEFT, RIGHT, DEADZONE};
        JoystickStates setCursorPos (int x, int y);
};