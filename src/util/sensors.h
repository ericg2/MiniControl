#include "Arduino.h"
#include "Keypad.h"
#include "LiquidCrystal.h"
#include "DHT.h"
#include "DHT_U.h"

#ifndef SENSORS_H
#define SENSORS_H

struct Sensors
{
    DHT           dht;
    LiquidCrystal lcd;
    Keypad        keypad;
    uint16_t      logPIN;
};

extern struct Sensors GlobalSensors;

#endif