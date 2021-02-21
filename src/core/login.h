#ifndef LOGIN_H
#define LOGIN_H

#include "util/sensors.h"
#include "LiquidCrystal.h"
#include "Keypad.h"

class Login 
{
    public:
        Login();
        void execute();

        // Tool Identification
        const char* toolName = "Login";
        const char* toolType = "core";
        const char* toolDesc = "A core service to allow logging in.";
};

#endif