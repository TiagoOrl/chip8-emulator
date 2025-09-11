#ifndef CHIP8_SCREEN_H
#define CHIP8_SCREEN_H

#include <stdbool.h>
#include "config.h"


struct screen
{
    bool pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
};


void chip8_screen_set(struct screen* screen, unsigned int x, unsigned int y);
bool chip8_screen_is_set(struct screen* screen, unsigned int x, unsigned int y);


#endif