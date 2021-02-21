/*
 * Login Tool for MiniControl Arduino
 * Copyright (c) 2021 houseofkraft
 * 
 * This core software is made for logging in to the Arduino
 * with a PIN code (which is specified in Software)
 * 
 * This software is licensed under the MIT license.
 */

#include "login.h"
#include "util/sensors.h"

int cursorX = 0;
String pin;

uint16_t getPIN()
{
    while (true)
    {
        char pressed = GlobalSensors.keypad.getKey();
        if (pressed)
        {
            if (pressed == 'A' || pressed == 'B' || pressed == 'C' || pressed == 'D') {} // ignore
            else
            {
                if (pressed == '#') break;
                if (cursorX >= 4)   break;
                cursorX++;
                pin.concat(pressed);
                GlobalSensors.lcd.clear();
                GlobalSensors.lcd.setCursor(0,0);
                GlobalSensors.lcd.print("PIN:");
                GlobalSensors.lcd.setCursor(0,1);
                GlobalSensors.lcd.print(pin);

                tone(13, 1000);
                delay(200);
                noTone(13);
            }
        }
    }
}

void loginMenu()
{
    pin = "";
    delay(2000);

    // Probably want to make a alias RIP
    GlobalSensors.lcd.clear();
    GlobalSensors.lcd.setCursor(0,0);
    GlobalSensors.lcd.print("MiniControl Login");
    GlobalSensors.lcd.setCursor(0,1);
    GlobalSensors.lcd.print("Enter PIN");
}

void Login::execute()
{

    while (true)
    {
        loginMenu();
        if (pin.toInt() != GlobalSensors.logPIN)
        {
            GlobalSensors.lcd.clear();
            GlobalSensors.lcd.setCursor(0,0);
            GlobalSensors.lcd.print("INCORRECT!");
            tone(13, 800, 200);
            delay(200);
            tone(13, 500, 200);
            delay(2000);
        } else
        {
            break;
        }
    }
    return;
}