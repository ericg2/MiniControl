/*
 * Mini Control for Arduino (Mega Recommended!)
 * Copyright (c) 2021 houseofkraft
 * 
 * This software is made for my Arduino setup with a 4x4 Keypad, RGB LED,
 * DHT11/22, Joystick, and LCD screen. I wanted this to be able to test
 * sensors mainly (by specifying the type and ports), solve Math Problems,
 * display the time, temperature/humidity, and as much things as I can think of.
 * 
 * Preferably I want this to be modular, for example I could attach an Ultrasonic
 * Sensor and use tools related to that like an alarm or distance reader. This
 * would also mean it could work with other people's setups and yours will not have
 * to be exactly like mine. 
 * 
 * Finally, I want this to be able to support "apps". These are basically like tools
 * and there will be a way to easily add more and each one will receive access to the LCD,
 * sensors, and everything the main program can access. Preferably having requirements so
 * some will only work with a certain type of sensor, etc.
 * 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LEGAL INFO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial 
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <Arduino.h>
#include <Keypad.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#include <util/sensors.h>
#include <core/login.h>
#include <core/list.h>

#define LCD_RS 12
#define LCD_E  11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

#define LOGIN_PIN 0000

// Define the keypad ports from Left --> Right (analog or digital)
// 4x4 keypad only!
#define L1 53
#define L2 52
#define L3 52
#define L4 A7
#define L5 A6
#define L6 A5
#define L7 A4
#define L8 A3

#define DHT_PIN 13
#define DHT_TYPE DHT11 //DHT22

#define CONTRAST_PIN 6
#define LCD_CONTRAST 100

///////////////////////////////////////////////////////////////////////////////////////////////////

const uint8_t KEYPAD_ROWS = 4;
const uint8_t KEYPAD_COLS = 4;

char keyMap[KEYPAD_ROWS][KEYPAD_COLS] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

uint8_t rowPins[KEYPAD_ROWS] = {L1, L2, L3, L4};
uint8_t colPins[KEYPAD_COLS] = {L5, L6, L7, L8};

LiquidCrystal lcdSensor(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Keypad keypadSensor = Keypad(makeKeymap(keyMap), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);
DHT dhtSensor(DHT_PIN, DHT_TYPE);


// Add the sensors to the global list.
struct Sensors GlobalSensors = (Sensors) 
{
    .dht = dhtSensor, 
    .lcd = lcdSensor,
    .keypad = keypadSensor,
    .logPIN = LOGIN_PIN
};

void setup()
{
    GlobalSensors.lcd.begin(16,2);
    GlobalSensors.dht.begin();

    GlobalSensors.lcd.setCursor(0,0);
    GlobalSensors.lcd.print("MiniControl");
    GlobalSensors.lcd.print("(c) 2021 | MIT");
    delay(1000);

    GlobalSensors.lcd.clear();
    digitalWrite(13, LOW);
    analogWrite(CONTRAST_PIN, LCD_CONTRAST);

    // Load the main login init script.
    GlobalToolList.init1.execute();
}

void loop(){}