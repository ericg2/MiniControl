#ifndef LIST_H
#define LIST_H

/*
 * Tool List Header
 * Copyright (c) 2021 houseofkraft
 * 
 * If you want to add a custom tool, make sure you go into the file here
 * and the list.cpp file to actually define the Class Type. 
 * 
 * NOTE: Make sure you also go into loader.cpp to add to the switch case
 * statement as well.
 */

#include <core/login.h>
#include "Arduino.h"

struct ToolList
{
    // Add the init tools (mostly from core)
    Login init1 = Login();

    // Make sure you add how many init scripts there are
    // and how many tools so the handler knows how many
    // times to check.
    uint16_t initScripts = 1;
    uint16_t toolScripts = 0;
};

extern struct ToolList GlobalToolList;

#endif