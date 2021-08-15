/* Copyright 2021 SimonTagne

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * Runs on Arduino micro.
 * Pinout:
 * ┌─┐   ┌─┐
 * │ └───┘ │
 * │ · · · │ SCL  NC  GND
 * │ · · · │ VCC  NC  SDA
 * └───────┘
 * 
 * SCL: Arduino pin 3
 * SDA: Arduino pin 2
 * VCC: 3.3V
 * GND: Ground
 * NC:  No connection
 * 
 * Mappings:
 * Jump: Z
 * Left/Right: Horizontal Joystick
 * 
 * Default keyboard bindings for Nidhogg
 */
#include <Keyboard.h>
#include <Wire.h>

#include "nunchuck_funcs.h"

//#define RIGHT_PLAYER
#define LEFT_PLAYER

#ifdef RIGHT_PLAYER
    #define KEY_JUMP 'n'
    #define KEY_RIGHT KEY_RIGHT_ARROW
    #define KEY_LEFT  KEY_LEFT_ARROW
#endif

#ifdef LEFT_PLAYER
    #define KEY_JUMP 'g'
    #define KEY_RIGHT 'd'
    #define KEY_LEFT 'a'
#endif

void setup() {
    // put your setup code here, to run once:
    // Initialize Nunchuck library
    nunchuck_init();
    // Initialize Keyboard library
    Keyboard.begin();
}

void loop() {
    // put your main code here, to run repeatedly:

    nunchuck_get_data();
    
    if(nunchuck_zbutton())
    {
        Keyboard.press(KEY_JUMP);
    }
    else
    {
        Keyboard.release(KEY_JUMP);
    }
    

    int joyx = nunchuck_joyx(); // Range is approximately 20-220, middle position is approximately 120

    if(joyx > 200)
    {
        Keyboard.press(KEY_RIGHT);
    }
    else
    {
        Keyboard.release(KEY_RIGHT);
    }

    if(joyx < 50)
    {
        Keyboard.press(KEY_LEFT);
    }
    else
    {
        Keyboard.release(KEY_LEFT);
    }

    delay(10);
}
